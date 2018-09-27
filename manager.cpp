#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <functional>

// stores binary heap as a vector
// Callback let element know if index was changed (does nothing by default)
// Compare defines priority
template < typename Element,
           typename Callback = std::function<void(const Element&, const int)>,
           typename Compare = std::less<Element> >
class BinaryHeap {
private:
  std::vector<Element> heap;

  int leftChild(const int index) const;
  int rightChild(const int index) const;
  int parent(const int index) const;

  void swap(const int first, const int second);
  
  void siftUp(int index);
  
  void siftDown(int index);

  void heapify(int index);

public:
  int size() const;

  void add(const Element& element);

  void remove(const int index);

  Element getMax() const;
};

// represents a block of memory
struct Block {
  int left;
  int size;
  bool empty;

  int heapIndex;

  Block(const int left,
        const int size,
        const bool empty = true,
        const int index = -1);
};

// compares two blocks (in doubly linked list) by size
// if sizes are equal, compares by the index of left cell:
// true if first has bigger index of left cell
bool operator<(const std::list<Block>::const_iterator& first,
               const std::list<Block>::const_iterator& second);

enum Type { ALLOCATE, RELEASE };

struct Query {
  Type type;

  // index of query for a "RELEASE" type of query
  int index;
  // size of block for an "ALLOCATE" type
  int size;
};

struct Response {
  Type type;
  int result;
};

Query readQuery(std::istream &inputStream = std::cin);

void readAll(int& size, std::vector<Query>& queries, std::istream &inputStream = std::cin);

struct ChangeIndex {
  void operator() (const std::list<Block>::iterator& block, const int index) const;
};

class MemoryManager {
private:
  BinaryHeap<std::list<Block>::iterator, ChangeIndex> heap;
  std::list<Block> blocks;
  std::vector< std::list<Block>::iterator > allocatedBlocks;

  // stands for allocating errors
  static const int allocatingError = -1;

  void mergeBlocks(const std::list<Block>::iterator first,
                   const std::list<Block>::iterator second);

  void tryMergingWithNext(const std::list<Block>::iterator block);

  void tryMergingWithPrevious(const std::list<Block>::iterator block);

public:
  explicit MemoryManager(const int size);

  // allocates a block of memory of certain size
  Response allocate(const int allocableSize);

  // releases previously allocated block #index
  Response release(const int index);
};

std::vector<Response> simulateMemoryManager(const int size, const std::vector<Query>& queries);

void printResponse(const Response& response, std::ostream &outputStream = std::cout);

void printResponses(const std::vector<Response> responses, std::ostream &outputStream = std::cout);

int main() {
  int size;
  std::vector<Query> queries;
  readAll(size, queries);

  std::vector<Response> responses = simulateMemoryManager(size, queries);

  printResponses(responses);

  return 0;
}

template <typename Element, typename Callback, typename Compare>
int BinaryHeap<Element, Callback, Compare>::size() const {
  return static_cast<int>(heap.size());
}

template <typename Element, typename Callback, typename Compare>
int BinaryHeap<Element, Callback, Compare>::leftChild(const int index) const {
  return 2 * index + 1;
}

template <typename Element, typename Callback, typename Compare>
int BinaryHeap<Element, Callback, Compare>::rightChild(const int index) const {
  return 2 * index + 2;
}

template <typename Element, typename Callback, typename Compare>
int BinaryHeap<Element, Callback, Compare>::parent(const int index) const {
  return (index - 1) / 2;
}

template <typename Element, typename Callback, typename Compare>
void BinaryHeap<Element, Callback, Compare>::swap(const int first, const int second) {
  Callback()(heap[first], second);
  Callback()(heap[second], first);

  std::swap(heap[first], heap[second]);
}

template <typename Element, typename Callback, typename Compare>
void BinaryHeap<Element, Callback, Compare>::add(const Element& element) {
  heap.push_back(element);
  Callback()(element, size() - 1);
  siftUp(size() - 1);
}

template <typename Element, typename Callback, typename Compare>
void BinaryHeap<Element, Callback, Compare>::remove(const int index) {
  swap(index, size() - 1);
  heap.pop_back();
  heapify(index);
}

template <typename Element, typename Callback, typename Compare>
void BinaryHeap<Element, Callback, Compare>::siftUp(int index) {
  int parentIndex = parent(index);
  while (index > 0 && index < size() && Compare()(heap[parentIndex], heap[index])) {
    swap(parentIndex, index);
    index = parentIndex;
    parentIndex = parent(index);
  }
}

template <typename Element, typename Callback, typename Compare>
void BinaryHeap<Element, Callback, Compare>::siftDown(int index) {
  int left, right, largest;
  while (!heap.empty()) {
    left = leftChild(index);
    right = rightChild(index);
    largest = index;

    if ( left < size() && Compare()(heap[largest], heap[left]) ) {
      largest = left;
    }
    if ( right < size() && Compare()(heap[largest], heap[right]) ) {
      largest = right;
    }

    if (largest == index) {
      break;
    }

    swap(index, largest);
    index = largest;
  }
}

template <typename Element, typename Callback, typename Compare>
void BinaryHeap<Element, Callback, Compare>::heapify(int index) {
  siftDown(index);
  siftUp(index);
}

template <typename Element, typename Callback, typename Compare>
Element BinaryHeap<Element, Callback, Compare>::getMax() const {
  return heap[0];
}

void ChangeIndex::operator() (const std::list<Block>::iterator& block, const int index) const {
  block->heapIndex = index;
}

Block::Block(const int left, const int size, const bool empty, const int index) {
  this->left = left;
  this->size = size;
  this->empty = empty;
  this->heapIndex = index;
}

MemoryManager::MemoryManager(const int size) {
  blocks.push_front(Block(1, size));

  heap.add(blocks.begin());
}

void MemoryManager::mergeBlocks(const std::list<Block>::iterator first,
                                const std::list<Block>::iterator second) {
  first->size += second->size;
  if (first->left > second->left) {
    first->left = second->left;
  }
  heap.remove(second->heapIndex);
  blocks.erase(second);
}

void MemoryManager::tryMergingWithNext(const std::list<Block>::iterator block) {
  if (blocks.end() != std::next(block, 1) && std::next(block, 1)->empty) {
    mergeBlocks(block, std::next(block, 1));
  }
}

void MemoryManager::tryMergingWithPrevious(const std::list<Block>::iterator block) {
  if (blocks.begin() != block && std::prev(block, 1)->empty) {
    mergeBlocks(block, std::prev(block, 1));
  }
}

Response MemoryManager::allocate(const int allocableSize) {
  Response response;
  response.type = ALLOCATE;
  allocatedBlocks.push_back(blocks.end());

  if (heap.size() < 1) {
    response.result = allocatingError;
    return response;
  }

  std::list<Block>::iterator block = heap.getMax();
  if (block->size < allocableSize) {
    response.result = allocatingError;
    return response;
  }

  heap.remove(0);
  if (block->size == allocableSize) {
    block->empty = false;
    response.result = block->left;
    allocatedBlocks.back() = block;
    return response;
  }

  block->left += allocableSize;
  block->size -= allocableSize;
  heap.add(block);
  block = blocks.insert(block,
                        Block(block->left - allocableSize, allocableSize, false));

  allocatedBlocks.back() = block;
  response.result = block->left;
  return response;
}

Response MemoryManager::release(const int index) {
  Response response;
  response.type = RELEASE;
  allocatedBlocks.push_back(blocks.end());

  std::list<Block>::iterator block = allocatedBlocks[index];
  if (block == blocks.end()) {
    return response;
  }

  tryMergingWithNext(block);
  tryMergingWithPrevious(block);

  block->empty = true;
  heap.add(block);

  return response;
}

Query readQuery(std::istream &inputStream) {
  Query query;
  int parameter;
  inputStream >> parameter;
  if (parameter > 0) {
    query.type = ALLOCATE;
    query.size = parameter;
  } else {
    query.type = RELEASE;
    query.index = -parameter - 1;
  }
  return query;
}

void readAll(int& size, std::vector<Query>& queries, std::istream& inputStream) {
  inputStream >> size;

  int numberOfQueries;
  inputStream >> numberOfQueries;

  queries = std::vector<Query>(numberOfQueries);
  for (int i = 0; i < numberOfQueries; ++i) {
    queries[i] = readQuery();
  }
}

bool operator<(const std::list<Block>::const_iterator& first,
  const std::list<Block>::const_iterator& second) {
    return first->size == second->size ? first->left > second->left : first->size < second->size;
}

std::vector<Response> simulateMemoryManager(const int size, const std::vector<Query>& queries) {
  MemoryManager memoryManager(size);

  std::vector<Response> responses;
  for (std::vector<Query>::const_iterator it = queries.begin(); it != queries.end(); ++it) {
    if (it->type == RELEASE) {
      responses.push_back(memoryManager.release(it->index));
    } else {
      responses.push_back(memoryManager.allocate(it->size));
    }
  }

  return responses;
}

void printResponse(const Response& response, std::ostream &outputStream) {
  if (response.type == ALLOCATE) {
    outputStream << response.result << "\n";
  }
}

void printResponses(const std::vector<Response> responses, std::ostream &outputStream) {
  for (std::vector<Response>::const_iterator it = responses.begin(); it != responses.end(); ++it) {
    printResponse(*it, outputStream);
  }
}
