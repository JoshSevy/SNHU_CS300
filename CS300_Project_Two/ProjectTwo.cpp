//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Joshua Sevy
// Version     : 1.0
// Description : Project Two ADCU Advising Assistance Program (Binary Search Tree)
//============================================================================

#include <iostream>
#include <sstream>
#include <vector>

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

//============================================================================
// Binary Search Tree class definition
//============================================================================

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

//============================================================================
// Helper methods
//============================================================================

/**
 * Display a course
 * @param course
 */
void displayCourse(Course course) {
  cout << course.courseNumber << ", " << course.courseTitle << endl;
}

/**
 * Convert string to uppercase
 * @param str
 * @return
 */
string toUpperCase(string str) {
  transform(str.begin(), str.end(), str.begin(), ::toupper);
  return str;
}

/**
 * Split CSV line into tokens
 * @param line
 * @return
 */
vector<string> split(string line) {
  vector<string> tokens;
  string token;
  stringstream ss(line);

  while (getline(ss, token, ',')) {
    tokens.push_back(token);
  }
  return tokens;
}

/**
 *
 * @return
 */
int main() {

  BinarySearchTree* bst = new BinarySearchTree();

  int choice = 0;
  string fileName;
  string courseNumber;

  cout << "Welcome to the course planner." << endl;

  while (choice != 9) {
    cout << "  1. Load Data Structure" << endl;
    cout << "  2. Print Course List" << endl;
    cout << "  3. Print Course" << endl;
    cout << "  4. Exit" << endl;
    cout << "What would you like to do?" << endl;
    cin >> choice;

    switch (choice) {
      case 1:
        cout << "Enter file name: ";
        cin >> fileName;
        // TODO: Implement loading file
        break;
      case 2:
        if (bst->isEmpty()) {
          cout << "No courses loaded."  << endl;
        } else {
          cout << "Here is a sample schedule:" << endl;
          bst->InOrder();
        }
        break;
      case 3:
        if (bst->isEmpty()) {
          cout << "No courses loaded."  << endl;
        } else {
          cout << "What course do you want to know about? ";
          cin >> courseNumber;
          courseNumber = toUpperCase(courseNumber);
          Course course = bst->Search(courseNumber);

          if (course.courseNumber.empty()) {
            cout << "Course not found." << endl;
          } else {
            cout << course.courseNumber << ", " << course.courseTitle << endl;

            if (course.prerequisites.empty()) {
              cout << "Prerequisites: None" << endl;
            } else {
              cout << "Prerequisites: ";
              for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites.at(i);
                if (i < course.prerequisites.size() - 1) {
                  cout << ", ";
                }
              }
              cout << endl;
            }
          }
        }
        break;
      case 9:
        cout << "Thank you for using the course planner!" << endl;
        break;
      default:
        cout << choice << " is not a valid option." << endl;
        break;
    }
  }

  delete bst;
  return 0;
}