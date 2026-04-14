//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Joshua Sevy
// Version     : 1.0
// Description : Project Two ABCU Advising Assistance Program (Binary Search Tree)
//============================================================================

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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

class BinarySearchTree;

// Forward declarations
void displayCourse(Course course);
void printPrerequisites(BinarySearchTree* bst, const vector<string>& prerequisites);

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
 * Trim whitespace from both ends of a string
 * @param str
 * @return
 */
string trim(const string &str) {
  // Find first non-space character
  size_t start = 0;
  while (start < str.length() && isspace(str[start])) {
    start++;
  }

  // Find last non-space character
  size_t end = str.length();
  while (end > start && isspace(str[end - 1])) {
    end--;
  }

  // Return substring between start and end
  return str.substr(start, end - start);
}

/**
 * Convert string to uppercase
 * @param str
 * @return
 */
string toUpperCase(string str) {
  for (size_t i = 0; i < str.length(); i++) {
    str[i] = static_cast<char>(toupper(str[i]));
  }

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
    tokens.push_back(trim(token));
  }
  return tokens;
}

/**
 * Validate that a course line contains at least a course number and title
 * @param tokens
 * @return
 */
bool isValidCourseLine(const vector<string>& tokens) {
  if (tokens.size() < 2) {
    return false;
  }

  if (tokens.at(0).empty() || tokens.at(1).empty()) {
    return false;
  }

  return true;
}

/**
 * Check if a prerequisite exists in the list of valid course numbers
 * @param prereq
 * @param validCourseNumbers
 * @return
 */
bool prerequisiteExists(const string& prereq, const vector<string>& validCourseNumbers) {
  for (const string& validCourse : validCourseNumbers) {
    if (prereq == validCourse) {
      return true;
    }
  }
  return false;
}

/**
 * Print prerequisite course numbers and titles
 * @param bst
 * @param prerequisites
 */
void printPrerequisites(BinarySearchTree* bst, const vector<string>& prerequisites) {
  if (prerequisites.empty()) {
    cout << "Prerequisites: None" << endl;
    return;
  }

  cout << "Prerequisites:" << endl;
  for (size_t i = 0; i < prerequisites.size(); ++i) {
    Course prereqCourse = bst->Search(prerequisites.at(i));

    if (!prereqCourse.courseNumber.empty()) {
      cout << prereqCourse.courseNumber << ", " << prereqCourse.courseTitle << endl;
    } else {
      // Fall back to course number if anything is missing
      cout << prerequisites.at(i) << endl;
    }
  }
}

void printCourse(BinarySearchTree* bst, string courseNumber) {
  Course course = bst->Search(toUpperCase(courseNumber));

  if (course.courseNumber.empty()) {
    cout << "Course not found." << endl;
    return;
  }

  cout << course.courseNumber << ", " << course.courseTitle << endl;
  printPrerequisites(bst, course.prerequisites);
}


void loadCourses(string fileName, BinarySearchTree*& bst) {
  ifstream file;
  file.open(fileName);

  if (!file.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  // Make sure tree is reset before loading a new file
  delete bst;
  bst = new BinarySearchTree();

  vector<string> rawLines;
  vector<string> validCourseNumbers;
  string line;

  cout << "Loading courses from file: " << fileName << endl;

  // First pass:
  // Read each line, validate the minimum format,
  // collect all course numbers for later prerequisite checks
  while (getline(file, line)) {
    line = trim(line);

    if (line.empty()) {
      continue;
    }

    vector<string> tokens = split(line);

    if (!isValidCourseLine(tokens)) {
      cout << "Invalid file format: " << line << endl;
      continue;
    }

    tokens.at(0) = toUpperCase(tokens.at(0));

    rawLines.push_back(line);
    validCourseNumbers.push_back(tokens.at(0));
  }

  file.close();

  // Second pass:
  // Build course objects and verify that each prerequisite exists
  for (int i = 0; i < rawLines.size(); i++) {
    vector<string> tokens = split(rawLines.at(i));

    Course newCourse;
    newCourse.courseNumber = toUpperCase(tokens.at(0));
    newCourse.courseTitle = tokens.at(1);

    vector<string> prereqList;
    bool isValid = true;

    for (int j = 2; j < tokens.size(); ++j) {
      string prereq = toUpperCase(tokens.at(j));

      if (!prerequisiteExists(prereq, validCourseNumbers)) {
        cout << "Invalid prerequisite: " << prereq << " for course " << newCourse.courseNumber << endl;
        isValid = false;
        break;
      }

      prereqList.push_back(prereq);
    }

    // Only store valid courses so bad data does no affect the tree
    if (isValid) {
      newCourse.prerequisites = prereqList;
      bst->InsertCourse(newCourse);
    }
  }
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
    cout << "  9. Exit" << endl;
    cout << "What would you like to do? ";
    cin >> choice;

    switch (choice) {
      case 1:
        cout << "Enter file name: ";
        cin >> fileName;
        loadCourses(fileName, bst);
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
          printCourse(bst, courseNumber);
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