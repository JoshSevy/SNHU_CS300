

#include <iostream>

using namespace std;

// TODO: ADD similar comments from previous assignment boilerplate

/**
 * A single course in the ABCU advising program.
 */
struct Course {
  string courseNumber;
  string courseTitle;
  vector<string> prerequisites;
};

// Forward declarations
void displayCourse(Course course);

struct Node {
  Course course;
  Node* left;
  Node* right;
};

//=====================================================================================================================
// Binary Search Tree class definition
//=====================================================================================================================

/**
 * Define a class implementing a binary search tree
 */
class BinarySearchTree {

private:
  struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
      left = nullptr;
      right = nullptr;
    }

    Node(Course aCourse): Node() {
      course = aCourse;
    }
  };

  Node* root;

  void addNode(Node* node, Course course);
  void inOrder(Node* node);
  Course search(Node* node, string courseNumber);
  void destroyTree(Node* node);

public:
  BinarySearchTree();
  virtual ~BinarySearchTree();
  void InsertCourse(Course course);
  void InOrder();
  Course Search(string courseNumber);
  bool isEmpty();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
  root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
  destroyTree(root);
  root = nullptr;
}

/**
 * Insert a course
 * @param course
 */
void BinarySearchTree::InsertCourse(Course course) {
  if (root == nullptr) {
    root = new Node(course);
  } else {
    addNode(root, course);
  }
}

/**
 * Add a node recursively
 * @param node
 * @param course
 */
void BinarySearchTree::addNode(Node* node, Course course) {
  if (course.courseNumber < node->course.courseNumber) {
    //
    if (node->left == nullptr) {
      node->left = new Node(course);
    } else {
      addNode(node->left, course);
    }
  } else {
    if (node->right == nullptr) {
      node->right = new Node(course);
    } else {
      addNode(node->right, course);
    }
  }
}

/**
 * In-order traversal
 */
void BinarySearchTree::InOrder() {
  inOrder(root);
}

void BinarySearchTree::inOrder(Node* node) {
  if (node != nullptr) {
    inOrder(node->left);
    displayCourse(node->course);
    inOrder(node->right);
  }
}

/**
 * Search for a course
 * @param courseNumber
 * @return Course
 */
Course BinarySearchTree::Search(string courseNumber) {
  return search(root, courseNumber);
}

Course BinarySearchTree::search(Node* node, string courseNumber) {
  while (node != nullptr) {
    if (node->course.courseNumber == courseNumber) {
      return node->course;
    }

    if (courseNumber < node->course.courseNumber) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return Course();
}

/**
 * Destroy tree (post-order cleanup)
 * @param node
 */
void BinarySearchTree::destroyTree(Node* node) {
  if (node != nullptr) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

bool BinarySearchTree::isEmpty() {
  return root == nullptr;
}

//=====================================================================================================================
// Helper methods
//=====================================================================================================================

/**
 *
 * @return
 */
int main() {
  // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.

  const auto lang = "C++";
  std::cout << "Hello and welcome to " << lang << "!\n";

  for (int i = 1; i <= 5; i++) {
    // TIP Press <shortcut actionId="Debug"/> to start debugging your code. We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/> breakpoint for you, but you can always add more by pressing <shortcut actionId="ToggleLineBreakpoint"/>.
    std::cout << "i = " << i << std::endl;
  }

  return 0;
  // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}