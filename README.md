# GitLite: A Lightweight Version Control System 🌟
GitLite is a simplified yet powerful version control system inspired by Git, designed to provide an efficient and secure way to manage large datasets. Built with C++, it employs Object-Oriented Programming (OOP) principles and advanced Data Structures, offering branching, commit history tracking, and custom tree-based data storage.

# ✨ Features
Version Control

Track changes with commit history.

Revert to previous versions when needed.

Branch Management

Create independent branches for parallel development.

Switch seamlessly between branches.

Custom Tree Storage

Use AVL Trees, B-Trees, or Red-Black Trees for organizing data.

Efficient memory management by storing tree nodes in separate files.

Commit Logs

View detailed commit history with timestamps and messages.

Collaborative-Friendly

Branching and secure data handling make it ideal for collaborative environments.
# 🛠 Key Functionalities
1. Initialize Repository
Command: init <filename>

Upload a CSV file and select a tree structure (AVL, B-Tree, or Red-Black Tree).
Store nodes as individual files, reducing memory overhead.

2. Commit Changes
Command: commit "message"

Save changes with descriptive commit messages for clear version tracking.

3. Create Branches
Command: branch <branch_name>

Create a new branch stored in its own folder for independent development.

4. Switch Branches
Command: checkout <branch_name>

Load the selected branch’s data to continue development.

5. View Commit History
Command: log

Display all commits for the current branch with timestamps and messages.
# ⚙️ How It Works
Initialization: Run init to upload data and choose a tree structure. Nodes are stored as files for optimized handling of large datasets.

Branching: Use branch to create separate workstreams. Each branch is represented as a folder containing the current repository state.

Commit Management: Use commit to save and track changes in the active branch.

Switching: Switch between branches with checkout to access their respective states.

Log History: Use log to review the commit history of the active branch.

# Contributors
Muhammad Talha Rashid

Afnan Rizwan

Abdullah Nasir Queshi

Feel free to contribute, raise issues, or provide feedback! 😊
