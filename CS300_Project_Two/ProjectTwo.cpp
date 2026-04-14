//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Joshua Sevy
// Version     : 1.0
// Description : Project Two ABCU Advising Assistance Program (Binary Search Tree)
//============================================================================

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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
void displayCourse(const Course& course);
void printPrerequisites(const BinarySearchTree* bst, const vector<string>& prerequisites);

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

    Node(Course singleCourse): Node() {
      course = singleCourse;
    }
  };

  Node* root;

  static void addNode(Node* node, const Course& course);
  static int countNodes(const Node* node);
  static void destroyTree(const Node* node);
  static void inOrder(const Node* node);
  static Course search(const Node* node, const string& courseNumber);

public:
  BinarySearchTree();
  virtual ~BinarySearchTree();
  void InOrder() const;
  void InsertCourse(const Course& course);
  bool isEmpty() const;
  Course Search(const string &courseNumber) const;
  int Size() const;
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
void BinarySearchTree::InsertCourse(const Course& course) {
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
void BinarySearchTree::addNode(Node* node, const Course& course) {
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
 * Get the number of courses in the tree
 * @return int
 */
int BinarySearchTree::Size() const {
  return countNodes(root);
}

int BinarySearchTree::countNodes(const Node* node) {
  if (node == nullptr) {
    return 0;
  }

  return 1 + countNodes(node->left) + countNodes(node->right);
}

/**
 * In-order traversal
 */
void BinarySearchTree::InOrder() const {
  inOrder(root);
}

void BinarySearchTree::inOrder(const Node* node) {
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
Course BinarySearchTree::Search(const string &courseNumber) const {
  return search(root, courseNumber);
}

Course BinarySearchTree::search(const Node* node, const string& courseNumber) {
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
void BinarySearchTree::destroyTree(const Node* node) {
  if (node != nullptr) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}

bool BinarySearchTree::isEmpty() const {
  return root == nullptr;
}

//============================================================================
// Helper methods
//============================================================================

/**
 * Display a course
 * @param course
 */
void displayCourse(const Course& course) {
  cout << course.courseNumber << ", " << course.courseTitle << endl;
}

/**
 * Trim whitespace from both ends of a string
 * @param str
 * @return string
 */
string trim(const string &str) {
  // Find first non-space character
  size_t start = 0;
  while (start < str.length() && isspace(static_cast<unsigned char>(str[start]))) {
    start++;
  }

  // Find last non-space character
  size_t end = str.length();
  while (end > start && isspace(static_cast<unsigned char>(str[end - 1]))) {
    end--;
  }

  // Return substring between start and end
  return str.substr(start, end - start);
}

/**
 * Convert string to uppercase
 * @param str
 * @return string
 */
string toUpperCase(string str) {
  for (size_t i = 0; i < str.length(); i++) {
    str[i] = static_cast<char>(toupper(static_cast<unsigned char>(str[i])));
  }

  return str;
}

/**
 * Split CSV line into tokens
 * @param line
 * @return vector<string>
 */
vector<string> split(const string& line) {
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
 * @return bool
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
 * @return bool
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
void printPrerequisites(const BinarySearchTree* bst, const vector<string>& prerequisites) {
  if (prerequisites.empty()) {
    cout << "Prerequisites: None" << endl;
    return;
  }

  cout << "Prerequisites:" << endl;
  for (const auto & prerequisite : prerequisites) {
    Course prereqCourse = bst->Search(prerequisite);

    if (!prereqCourse.courseNumber.empty()) {
      cout << prereqCourse.courseNumber << ", " << prereqCourse.courseTitle << endl;
    } else {
      // Fall back to course number if anything is missing
      cout << prerequisite << endl;
    }
  }
}

void printCourse(const BinarySearchTree* bst, const string &courseNumber) {
  Course course = bst->Search(toUpperCase(courseNumber));

  if (course.courseNumber.empty()) {
    cout << "Course not found." << endl;
    return;
  }

  cout << course.courseNumber << ", " << course.courseTitle << endl;
  printPrerequisites(bst, course.prerequisites);
}

/**
 * Load courses from a CSV file and insert them into the binary search tree
 * @param fileName
 * @param bst
 */
void loadCourses(const string& fileName, BinarySearchTree*& bst) {
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

  cout << "Courses loaded successfully." << endl;

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
  for (const auto & rawLine : rawLines) {
    vector<string> tokens = split(rawLine);

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

    // Only store valid courses so bad data does not affect the tree
    if (isValid) {
      newCourse.prerequisites = prereqList;
      bst->InsertCourse(newCourse);
    }
  }

  cout << bst->Size() << " courses loaded." << endl;
}

/**
 * The one and only main() method
 */
int main() {

  BinarySearchTree* bst = new BinarySearchTree();

  int choice = 0;
  string fileName;
  string courseNumber;

  cout << "Welcome to the course planner." << endl;

  while (choice != 9) {
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
    cin >> choice;

    // Handle invalid input
    if (cin.fail()) {
      cin.clear(); // reset error state
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
      cout << "Invalid input. Please enter a valid number." << endl;
      continue; // restart loop, display menu choices
    }

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