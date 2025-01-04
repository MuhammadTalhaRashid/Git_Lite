/*
Abdullah Nasir 23i-0726
Talha Rashid 23i-3050
Afnan Rizwan 23i-0561

*/




#include <iostream>
#include <fstream>
#include <cmath>
// #include <openssl/sha.h>
// #include<string>
#include <Windows.h>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using namespace std;

void setConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to print a single line of the box
void printLine(int width, char startChar, char midChar, char endChar)
{
    std::cout << startChar;
    for (int i = 1; i < width - 1; ++i)
    {
        std::cout << midChar;
    }
    std::cout << endChar << std::endl;
}
char* n1;
char* n2;

void intToCharArray(int num, char*& output)
{
    // Find the number of digits in the integer
    int temp = num;
    int length = 0;
    bool isNegative = false;

    // Check if the number is negative
    if (num < 0)
    {
        isNegative = true;
        temp = -temp; // Make the number positive for digit counting
        length++;
    }

    // Count the digits
    do
    {
        length++;
        temp /= 10;
    } while (temp != 0);

    // Allocate memory for the char array
    output = new char[length + 1]; // +1 for the null terminator

    // If the number is negative, add the negative sign
    if (isNegative)
    {
        output[0] = '-';
    }

    // Convert the integer to char array
    int i = length - 1;
    temp = num < 0 ? -num : num; // Use the absolute value
    if (temp == 0)
    {
        output[i] = (0) + '0';
    }
    else
    {
        while (temp > 0)
        {
            output[i--] = (temp % 10) + '0'; // Convert digit to char
            temp /= 10;
        }
    }

    // Null terminate the string
    output[length] = '\0';
}

class RBTree
{
private:
    char* root;
    bool setCheck;
    char* currentDir;
    bool setBool = true;

public:
    RBTree(char* cd)
    {
        root = NULL;
        setCheck = true;
        // Copy the directory path
        copyData(currentDir, cd);

        // Create the "root.txt" file
        char arr[256];
        int count = 0;

        // Copy cd into arr
        while (cd[count] != '\0')
        {
            arr[count] = cd[count];
            count++;
        }

        // Append "/root.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'r';
        arr[count++] = 'o';
        arr[count++] = 'o';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        // Create and write to "root.txt"
        std::ofstream object(arr);
        if (object.is_open())
        {
            object << "NULL";
            object.close();
        }
        else
        {
            std::cerr << "Failed to create file: " << arr << "\n";
        }

        // Reset arr and count for "commit.txt"
        count = 0;
        while (cd[count] != '\0')
        {
            arr[count] = cd[count];
            count++;
        }

        // Append "/commit.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'c';
        arr[count++] = 'o';
        arr[count++] = 'm';
        arr[count++] = 'm';
        arr[count++] = 'i';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        // Create and write to "commit.txt"
        std::ofstream object1(arr);
        if (object1.is_open())
        {
            object1.close();
        }
        else
        {
            std::cerr << "Failed to create file: " << arr << "\n";
        }
    }
    void inorder(char* node, int level)
    {

        if (node == NULL)
            return;

        preorder(getLeftChild(node), level + 1);
        for (int i = 0; i < level; i++)
            cout << "-";
        cout << ">";
        cout << node << endl;
        preorder(getRightChild(node), level + 1);
    }
    void callInorder(char* node)
    {
        inorder(node, 0);
        cout << endl;
    }

    void preorder(char* node, int level)
    {

        if (node == NULL)
            return;

        for (int i = 0; i < level; i++)
            cout << "-";
        cout << ">";
        cout << node << endl;

        preorder(getLeftChild(node), level + 1);
        preorder(getRightChild(node), level + 1);
    }
    void callPreorder(char* node)
    {
        preorder(node, 0);
        cout << endl;
    }

    void postorder(char* node, int level)
    {

        if (node == NULL)
            return;

        preorder(getLeftChild(node), level + 1);
        preorder(getRightChild(node), level + 1);
        for (int i = 0; i < level; i++)
            cout << "-";
        cout << ">";
        cout << node << endl;
    }
    void callPostorder(char* node)
    {
        postorder(node, 0);
        cout << endl;
    }

    char* findMinNode(char* node)
    {
        if (node == NULL)
            return NULL;

        while (getLeftChild(node) != NULL)
        {
            node = getLeftChild(node);
        }
        return node;
    }

    void removeFixUp(char* x)
    {
        while (x != root && getColor(x) == 0)
        {
            bool isLeftChild = compareValues(getLeftChild(getParent(x)), x);
            char* sibling;

            if (isLeftChild)
                sibling = getRightChild(getParent(x));
            else
                sibling = getLeftChild(getParent(x));

            // Case 1: Sibling is red
            if (getColor(sibling) == 1)
            {
                setColor(sibling, 0);
                setColor(getParent(x), 1);

                if (isLeftChild)
                    rotateLeft(getParent(x));
                else
                    rotateRight(getParent(x));

                sibling = isLeftChild ? getRightChild(getParent(x)) : getLeftChild(getParent(x));
            }

            // Case 2: Sibling's children are black
            if ((getLeftChild(sibling) == NULL || getColor(getLeftChild(sibling)) == 0) &&
                (getRightChild(sibling) == NULL || getColor(getRightChild(sibling)) == 0))
            {
                setColor(sibling, 1);
                x = getParent(x);
            }
            else
            {
                // Case 3: At least one of sibling's children is red
                if (isLeftChild &&
                    (getRightChild(sibling) == NULL || getColor(getRightChild(sibling)) == 0))
                {
                    setColor(getLeftChild(sibling), 0);
                    setColor(sibling, 1);
                    rotateRight(sibling);
                    sibling = getRightChild(getParent(x));
                }
                else if (!isLeftChild &&
                    (getLeftChild(sibling) == NULL || getColor(getLeftChild(sibling)) == 0))
                {
                    setColor(getRightChild(sibling), 0);
                    setColor(sibling, 1);
                    rotateLeft(sibling);
                    sibling = getLeftChild(getParent(x));
                }

                // Case 4: Recolor and rotate
                setColor(sibling, getColor(getParent(x)));
                setColor(getParent(x), 0);

                if (isLeftChild)
                {
                    setColor(getRightChild(sibling), 0);
                    rotateLeft(getParent(x));
                }
                else
                {
                    setColor(getLeftChild(sibling), 0);
                    rotateRight(getParent(x));
                }

                x = root;
            }
        }

        setColor(x, 0);
    }

    char* removeNode(char* node, char* filename)
    {
        if (node == NULL)
            return NULL;

        int nodeHash = getHash(node);
        int fileHash = getHash(filename);

        if (fileHash < nodeHash)
        {
            setLeftChild(node, removeNode(getLeftChild(node), filename), setCheck);
        }
        else if (fileHash > nodeHash)
        {
            setRightChild(node, removeNode(getRightChild(node), filename), setCheck);
        }
        else
        {
            char* childToReplace = NULL;
            if (getLeftChild(node) == NULL)
            {
                childToReplace = getRightChild(node);
            }
            else if (getRightChild(node) == NULL)
            {
                childToReplace = getLeftChild(node);
            }
            else
            {
                char* successor = findMinNode(getRightChild(node));
                setRightChild(node, removeNode(getRightChild(node), successor), setCheck);

                return node;
            }

            if (childToReplace != NULL)
            {
                replace_line(node, 4, getParent(node));           // Update parent
                replace_line(childToReplace, 4, getParent(node)); // Update child's parent
            }

            if (compareValues(node, root))
            {
                copyData(root, childToReplace);
            }
            else
            {

                bool isLeftChild = compareValues(getLeftChild(getParent(node)), node);

                if (isLeftChild)
                    setLeftChild(getParent(node), childToReplace, setCheck);
                else
                    setRightChild(getParent(node), childToReplace, setCheck);
            }

            if (getColor(node) == 0 && childToReplace != NULL)
            {
                removeFixUp(childToReplace);
            }

            // Free or delete file
            if (fs::exists(node))
            {
                fs::remove(node);
            }

            return childToReplace;
        }

        setHeight(node, 1 + max(height(getLeftChild(node)), height(getRightChild(node))));

        return node;
    }

    void remove(char* filename)
    {
        setCheck = true;
        removeNode(root, filename);
    }

    char* getRoot()
    {
        return root;
    }

    int calDataHash(char* line)
    {

        int i = 0;
        int final = 0;
        while (1)
        {
            if (line[i] == '\0')
                break;

            if (line[i] == ',')
            {
                i++;
                continue;
            }

            final += int(line[i]);
            i++;
        }
        return final;
    }

    void makeMerkel(const char* orgm, const char* newm, char* node, int& val, bool check)
    {

        if (getParent(node) == NULL)
        {
            if (!setBool)
                return;
            setBool = false;
            char* temp = new char[256];
            char* temp2 = new char[256];
            int i = 0;
            if (check)
            {

                while (orgm[i] != '\0')
                {
                    temp[i] = orgm[i];
                    temp2[i] = orgm[i];
                    i++;
                }
            }
            else
            {
                while (newm[i] != '\0')
                {
                    temp[i] = newm[i];
                    temp2[i] = orgm[i];
                    i++;
                }
            }

            int j = i;
            temp[i++] = '/';
            temp[i++] = 'r';
            temp[i++] = 'o';
            temp[i++] = 'o';
            temp[i++] = 't';
            temp[i++] = '.';
            temp[i++] = 't';
            temp[i++] = 'x';
            temp[i++] = 't';
            temp[i] = '\0';


            int l = 0;
            while (node[l] != '/')
                l++;
            while (node[l] != '\0') {
                temp2[j++] = node[l++];
            }
            temp2[j] = '\0';

            ofstream obj1;
            obj1.open(temp, ios::out);



            obj1 << temp2 << "\n";
            obj1.close();

            if (check)
                copyData(::n1, temp);
            else
                copyData(::n2, temp);
        }

        if (node == NULL)
            return;

        if (getLeftChild(node) == NULL && getRightChild(node) == NULL)
        {

            ifstream obj;
            obj.open(node, ios::in);
            char* linetemp = new char[1024];
            obj.getline(linetemp, 1024);
            int tmp = calDataHash(linetemp);
            val += tmp;
            obj.close();
        }
        else
        {
            int lv = 0;
            int rv = 0;
            makeMerkel(orgm, newm, getLeftChild(node), lv, check);
            makeMerkel(orgm, newm, getRightChild(node), rv, check);
            val = lv + rv;
        }

        ofstream obj2;
        char* newname = new char[256];
        int i = 0;
        if (check)
        {

            while (orgm[i] != '\0')
            {
                newname[i] = orgm[i];
                i++;
            }
        }
        else
        {
            while (newm[i] != '\0')
            {
                newname[i] = newm[i];
                i++;
            }
        }

        int j = 0;
        while (node[j] != '/')
        {
            j++;
        }

        while (node[j] != '\0')
        {
            newname[i++] = node[j++];
        }
        newname[i] = '\0';

        obj2.open(newname, ios::out);
        char* res = new char[50];
        intToCharArray(val, res);
        obj2 << res << "\n";
        if (getParent(node) == NULL)
            obj2 << "NULL\n";
        else
            obj2 << getParent(node) << "\n";

        if (getLeftChild(node) == NULL)
            obj2 << "NULL\n";
        else
            obj2 << getLeftChild(node) << "\n";

        if (getRightChild(node) == NULL)
            obj2 << "NULL\n";
        else
            obj2 << getRightChild(node) << "\n";

        obj2.close();

        /*if (getLeftChild(node) == NULL && getRightChild(node) == NULL) {
            makeMerkel(orgm, newm, getLeftChild(node), val, check);
            ::count--;
            makeMerkel(orgm, newm, getRightChild(node), val, check);
            ::count++;

            if (::count != 3)
            {
                ifstream obj;
                char* linetemp = new char[1024];
                obj.open(node, ios::in);
                obj.getline(linetemp, 1024);
                calDataHash(linetemp, val);
                obj.close();
            }

            if (::count == 3) {
                ofstream obj2;
                char* newname = new char[256];
                int i = 0;
                if (check) {

                    while (orgm[i] != '\0') {
                        newname[i] = orgm[i];
                        i++;
                    }
                }
                else {
                    while (newm[i] != '\0') {
                        newname[i] = newm[i];
                        i++;
                    }
                }

                int j = 0;
                while (node[j] != '/') {
                    j++;
                }

                while (node[j] != '\0') {
                    newname[i++] = node[j++];
                }
                newname[i] = '\0';


                obj2.open(newname, ios::out);
                char* res = new char[50];
                intToCharArray(temp, res);
                obj2 << res;
                obj2 << "\n";
                obj2.close();

                ::count = 0;
                temp = 0;
            }
            else
                temp += val;
        }
        else
            ::count--;*/
    }

    void callMerkel(const char* orgm, const char* newm, char* node)
    {

        bool check = false;
        if (fs::exists(orgm))
        {
            if (fs::exists(newm))
            {

                fs::rename(newm, orgm);
                if (fs::create_directory(fs::path(newm)))
                {
                    check = false;
                    cout << "Sub-Branch'" << newm << "' for Merkle Tree created successfully." << endl;
                }
            }
            else
            {

                if (fs::create_directory(fs::path(newm)))
                {
                    check = false;
                    cout << "Sub-Branch'" << newm << "' for Merkle Tree created successfully." << endl;
                }
            }
        }
        else
        {
            check = true;
            if (fs::create_directory(fs::path(orgm)))
            {
                cout << "Sub-Branch'" << orgm << "' for Merkle Tree created successfully." << endl;
            }
        }

        int val = 0;
        makeMerkel(orgm, newm, node, val, check);
        cout << "\nMerkle Tree Formed!" << endl;
    }

    bool compareHashVal(int a, int b)
    {
        if (a == b)
            return true;
        return false;
    }

    int calA(ifstream& obj1, char* line)
    {
        obj1.getline(line, 1024);
        int val = charArrayToInt(line);
        return val;
    }

    int calB(ifstream& obj2, char* line)
    {
        obj2.getline(line, 1024);
        int val = charArrayToInt(line);
        return val;
    }

    void callCompare(ifstream& obj1, ifstream& obj2, char* n1, char* n2, char*& temp, char* line)
    {

        if ((getRightChild(n1) == NULL && getLeftChild(n1) == NULL) || (getRightChild(n2) == NULL && getLeftChild(n2) == NULL))
            return;

        obj1.open(n1, ios::in);
        obj2.open(n2, ios::in);

        if (!(calA(obj1, line) != calA(obj2, line)))
        {
            copyData(temp, n1);
            obj1.close();
            obj2.close();
            return;
        }
        else
        {
            obj1.close();
            obj2.close();
            callCompare(obj1, obj2, getLeftChild(n1), getLeftChild(n2), temp, line);
            callCompare(obj1, obj2, getRightChild(n1), getRightChild(n2), temp, line);
        }
    }

    void comapreMerkle(const char* orgm, const char* newm)
    {

        ifstream obj1;
        ifstream obj2;

        char* temp;
        char* linetemp = new char[256];
        callCompare(obj1, obj2, ::n1, ::n2, temp, linetemp);
    }

    int height(char* node)
    {

        if (node == NULL)
            return 0;

        ifstream obj;
        obj.open(node, ios::in);
        char* linetemp = new char[1024];
        getLineValue(obj, linetemp, 2);
        obj.close();

        int a = charArrayToInt(linetemp);
        delete[] linetemp;
        return a;
    }

    int balanceFactor(char* node)
    {

        if (node != NULL)
            return (height(getLeftChild(node)) - height(getRightChild(node)));
        return 0;
    }
    // Most helper functions remain the same as AVL tree
    void copyData(char*& text, char* a)
    {
        text = new char[1024];
        int i = 0;
        while (a[i] != '\0')
        {
            text[i] = a[i];
            i++;
        }
        text[i] = '\0';
    }
    bool detectDirection(char* now, char* parent)
    {
        if (parent == NULL)
            return false;

        char* leftChild = getLeftChild(parent);

        // If leftChild is NULL, then 'now' must be the right child
        if (leftChild == NULL)
            return true;

        // Compare if 'now' is the same as leftChild
        return !compareValues(now, leftChild);
    }
    int stringConverter(char* text)
    {
        int i = 0;
        int final = 1;
        while (text[i] != '/')
            i++;
        i++;
        while (text[i] != '.')
        {
            int tell = int(text[i]);
            final *= tell;
            i++;
        }

        return final;
    }

    int valConverter(char* text)
    {
        int i = 0;
        int final = 1;
        while (text[i] != '/')
            i++;
        i++;
        while (text[i] != '.')
        {
            int tell = text[i] - '0';
            final *= tell;
            i++;
        }

        return final;
    }

    char* valChecker(char* text, int rowVal)
    {
        int i = 0;
        bool check = false;
        while (text[i] != '/')
            i++;
        i++;
        while (text[i] != '.')
        {
            if (!(text[i] >= '0' && text[i] <= '9'))
            {
                check = true;
                break;
            }
            i++;
        }
        int finalVal = 0;
        if (check)
            finalVal = stringConverter(text);
        else
            finalVal = valConverter(text);

        finalVal *= rowVal;
        finalVal = finalVal % 29;
        char* finalHash;
        intToCharArray(finalVal, finalHash);
        cout << endl
            << "Hash: " << finalVal << endl;
        cout << "Final Name: " << text << endl;
        return finalHash;
    }

    void intToCharArray(int num, char*& output)
    {
        // Find the number of digits in the integer
        int temp = num;
        int length = 0;
        bool isNegative = false;

        // Check if the number is negative
        if (num < 0)
        {
            isNegative = true;
            temp = -temp; // Make the number positive for digit counting
            length++;
        }

        // Count the digits
        do
        {
            length++;
            temp /= 10;
        } while (temp != 0);

        // Allocate memory for the char array
        output = new char[length + 1]; // +1 for the null terminator

        // If the number is negative, add the negative sign
        if (isNegative)
        {
            output[0] = '-';
        }

        // Convert the integer to char array
        int i = length - 1;
        temp = num < 0 ? -num : num; // Use the absolute value
        if (temp == 0)
        {
            output[i] = (0) + '0';
        }
        else
        {
            while (temp > 0)
            {
                output[i--] = (temp % 10) + '0'; // Convert digit to char
                temp /= 10;
            }
        }

        // Null terminate the string
        output[length] = '\0';
    }

    int charArrayToInt(const char* str)
    {
        int result = 0;
        bool isNegative = false;

        // Handle negative numbers
        if (str[0] == '-')
        {
            isNegative = true;
            str++; // Skip the negative sign
        }

        // Convert each character to its numeric value and accumulate
        for (int i = 0; str[i] != '\0'; ++i)
        {
            // Check if the character is a valid digit
            if (str[i] < '0' || str[i] > '9')
            {
                std::cerr << "Error: Invalid character in string" << std::endl;
                return 0; // Error case, invalid input
            }

            // Convert the character to an integer (digit) and add to result
            result = result * 10 + (str[i] - '0');
        }

        // If the number was negative, convert the result to negative
        if (isNegative)
        {
            result = -result;
        }

        return result;
    }
    int getCharPtrValue(const char* a)
    {
        int i = 0;
        while (a[i] != '\0')
            i++;
        return i;
    }
    bool compareValues(const char* a, const char* b)
    {
        if (a == NULL && b == NULL)
            return true;

        if (a == NULL || b == NULL)
            return false;

        if (getCharPtrValue(a) != getCharPtrValue(b))
            return false;
        else
        {
            int i = 0;
            while (a[i] != '\0')
            {
                if (a[i] != b[i])
                    return false;
                i++;
            }
            return true;
        }
    }

    void replace_line(char* parent, int line, const char* text)
    {

        ifstream obj1;
        ofstream obj2;

        obj1.open(parent, ios::in);
        obj2.open("temp.txt", ios::out | ios::trunc);

        // node parent change
        char* linetemp = new char[1024];
        int i = 0;
        obj1.getline(linetemp, 1024);
        while (linetemp[0] != '\0')
        {
            if (i != line - 1)
            {
                obj2 << linetemp;
                obj2 << "\n";
            }
            else
            {
                obj2 << text;
                obj2 << "\n";
            }
            i++;
            obj1.getline(linetemp, 1024);
        }
        delete[] linetemp;
        obj1.close();
        obj2.close();

        if (fs::exists(parent))
        {
            fs::remove(parent);
            // std::cout << "File deleted: " << parent << std::endl;
        }
        else
        {
            // std::cout << "File not found: " << parent << std::endl;
        }

        fs::rename("temp.txt", parent);
    }
    char* makeDefaultFile(char* filename, char** values, int index, char* parent, int rowVal, bool lc_check, bool rc_check, int color)
    {

        ofstream obj;
        obj.open(filename, std::ios::app);
        if (!obj.is_open())
        {
            std::cerr << "Failed to open or create file: " << filename << std::endl;
            return NULL;
        }

        // data copy
        if (values != NULL)
        {

            for (int i = 0; i <= index; i++)
                obj << values[i];
            obj << "\n";
        }
        else
            obj << "NULL\n";

        // height copy
        obj << "1\n";

        // hashcopy
        obj << valChecker(filename, rowVal);
        obj << "\n";

        // parent copy
        if (parent != NULL)
        {
            obj << parent;
            obj << "\n";
        }
        else
            obj << "NULL\n";

        // child 1 copy
        obj << "NULL\n";

        // child 2 copy
        obj << "NULL\n";

        if (color)
            obj << "1\n"; // red
        else
            obj << "0\n"; // black

        obj.close();

        return filename;
        // cout << "\nalldone\n" << endl;
        // system("pause");
    }

    // Existing helper functions like intToCharArray, charArrayToInt,
    // compareValues, getLineValue, etc. remain the same
    int getHash(const char* text)
    {
        ifstream obj;
        obj.open(text, ios::in);
        char* temptext = new char[1024];
        for (int i = 0; i < 3; i++)
            obj.getline(temptext, 1024);

        int val = charArrayToInt(temptext);
        delete[] temptext;
        obj.close();
        return val;
    }

    void getLineValue(ifstream& obj, char*& linetemp, int val)
    {

        for (int i = 0; i < val; i++)
            obj.getline(linetemp, 1024);
    }

    char* getLeftChild(const char* text)
    {
        if (text == NULL)
            return NULL;

        ifstream obj;
        obj.open(text, ios::in);
        char* temptext = new char[1024];

        getLineValue(obj, temptext, 5);

        // char* finalleft = new char[256];
        char* finalleft;
        copyData(finalleft, temptext);
        obj.close();
        delete[] temptext;

        if (compareValues(finalleft, "NULL"))
            return NULL;
        return finalleft;
    }

    char* getRightChild(const char* text)
    {
        if (text == NULL)
            return NULL;

        ifstream obj;
        obj.open(text, ios::in);
        char* temptext = new char[1024];
        getLineValue(obj, temptext, 6);

        // char* finalright = new char[256];
        char* finalright;
        copyData(finalright, temptext);
        delete[] temptext;
        obj.close();

        if (compareValues(finalright, "NULL"))
            return NULL;
        return finalright;
    }

    void setHeight(char* text, int val)
    {
        char* intChar;
        intToCharArray(val, intChar);
        replace_line(text, 2, intChar);
    }

    int calHash(char* node, int rowVal)
    {
        return charArrayToInt(valChecker(node, rowVal));
    }

    void setLeftChild(char* parent, char* lc, bool check)
    {
        if (!check)
            return;
        replace_line(parent, 5, lc);
    }

    void setRightChild(char* parent, char* rc, bool check)
    {
        if (!check)
            return;
        replace_line(parent, 6, rc);
    }

    int countLines(char* filename)
    {
        ifstream obj;
        obj.open(filename, ios::in);

        char* linetemp = new char[1024];
        int lineCount = 0;

        while (obj.getline(linetemp, 1024))
        {
            lineCount++;
        }

        obj.close();
        delete[] linetemp;

        return lineCount;
    }
    void setColor(char* text, bool colorChoice)
    {
        char* color = new char[2];
        if (!colorChoice)
            color[0] = '0';
        else
            color[0] = '1';
        color[1] = '\0';

        replace_line(text, 7, color);
        delete[] color;
    }

    char* grandparent(const char* node)
    {
        if (node == NULL)
            return NULL;

        ifstream obj;
        obj.open(node, ios::in);
        char* parent = new char[1024];
        getLineValue(obj, parent, 4);
        obj.close();

        if (compareValues(parent, "NULL"))
        {
            delete[] parent;
            return NULL;
        }

        obj.open(parent, ios::in);
        char* grandparent = new char[1024];
        getLineValue(obj, grandparent, 4);
        obj.close();

        if (compareValues(grandparent, "NULL"))
        {
            delete[] grandparent;
            return NULL;
        }
        return grandparent;
    }

    char* findUncle(char* node)
    {
        char* gp = new char[256];
        char* parent = new char[256];
        copyData(gp, grandparent(node));
        if (gp == NULL || compareValues(gp, "NULL"))
        {
            delete[] gp;
            delete[] parent;
            return NULL;
        }
        copyData(parent, getParent(node));

        ifstream obj;
        obj.open(gp, ios::in);
        char* leftChild = new char[1024];
        getLineValue(obj, leftChild, 5);
        obj.close();

        if (compareValues(parent, leftChild))
        {
            delete[] parent;
            return getRightChild(gp);
        }
        delete[] parent;

        return getLeftChild(gp);
    }

    char* getParent(const char* text)
    {
        if (text == NULL)
            return NULL;

        ifstream obj;
        obj.open(text, ios::in);
        char* temptext = new char[1024];

        getLineValue(obj, temptext, 4);

        char* finalval = new char[256];
        copyData(finalval, temptext);
        delete[] temptext;

        obj.close();

        if (compareValues(finalval, "NULL"))
        {
            delete[] finalval;
            return NULL;
        }
        return finalval;
    }

    char* rotateRight(char* now)
    {
        bool direction; // tells if the current now is left or right child of the parent.... false= left, true = right
        char* file1;
        copyData(file1, now);
        char* left = new char[256];
        char* rightOfLeft = new char[256];
        char* parent = new char[256];
        ifstream obj1;
        ifstream obj2;
        obj1.open(file1, ios::in);
        getLineValue(obj1, left, 5);
        obj1.clear();                 // Clear any error flags
        obj1.seekg(0, std::ios::beg); // Reset the pointer to the beginning of the file
        getLineValue(obj1, parent, 4);

        obj1.close();

        obj2.open(left, ios::in);
        getLineValue(obj2, rightOfLeft, 6);
        obj2.close();
        replace_line(file1, 5, rightOfLeft);
        replace_line(rightOfLeft, 4, file1);

        replace_line(left, 6, file1);
        replace_line(file1, 4, left);
        replace_line(left, 4, parent);

        if (!compareValues(parent, "NULL"))
        {
            direction = detectDirection(now, parent);

            if (direction)
                replace_line(parent, 6, left);
            else
                replace_line(parent, 5, left);
        }

        setHeight(file1, 1 + max(height(getLeftChild(file1)), height(getRightChild(file1))));
        setHeight(left, 1 + max(height(getLeftChild(left)), height(getRightChild(left))));
        setHeight(parent, 1 + max(height(getLeftChild(parent)), height(getRightChild(parent))));

        delete[] parent;
        delete[] rightOfLeft;

        return left;
    }

    char* rotateLeft(char* now)
    {
        bool direction; // tells if the current now is left or right child of the parent.... false= left, true = right
        char* file1;
        copyData(file1, now);
        char* right = new char[256];
        char* leftOfRight = new char[256];
        char* parent = new char[256];
        ifstream obj1;
        ifstream obj2;
        obj1.open(file1, ios::in);
        getLineValue(obj1, right, 6);
        obj1.clear();                 // Clear any error flags
        obj1.seekg(0, std::ios::beg); // Reset the pointer to the beginning of the file
        getLineValue(obj1, parent, 4);
        obj1.close();

        obj2.open(right, ios::in);
        getLineValue(obj2, leftOfRight, 5);
        obj2.close();
        replace_line(file1, 6, leftOfRight);
        replace_line(leftOfRight, 4, file1);

        // obj2.open(right, ios::in);
        replace_line(right, 5, file1);
        replace_line(file1, 4, right);
        replace_line(right, 4, parent);
        // obj2.close();

        if (!compareValues(parent, "NULL"))
        {
            direction = detectDirection(now, parent);

            if (direction)
                replace_line(parent, 6, right);
            else
                replace_line(parent, 5, right);
        }

        setHeight(file1, 1 + max(height(getLeftChild(file1)), height(getRightChild(file1))));
        setHeight(right, 1 + max(height(getLeftChild(right)), height(getRightChild(right))));
        setHeight(parent, 1 + max(height(getLeftChild(parent)), height(getRightChild(parent))));

        delete[] parent;
        delete[] leftOfRight;
        return right;
    }

    char* rebalance(char* node)
    {

        int bf = balanceFactor(node);
        if (bf > 1)
        {
            if (balanceFactor(getLeftChild(node)) < 0)
            {
                setLeftChild(node, rotateLeft(getLeftChild(node)), setCheck);
            }
            return rotateRight(node);
        }
        else if (bf < -1)
        {
            if (balanceFactor(getRightChild(node)) > 0)
            {
                setRightChild(node, rotateRight(getRightChild(node)), setCheck);
            }
            return rotateLeft(node);
        }

        return node;
    }

    int getColor(const char* text)
    {
        if (text == NULL)
            return NULL;

        ifstream obj;
        obj.open(text, ios::in);
        char* temptext = new char[1024];

        getLineValue(obj, temptext, 7);

        char* finalval = new char[256];
        copyData(finalval, temptext);
        obj.close();

        int val = charArrayToInt(finalval);
        delete[] temptext;
        delete[] finalval;
        return val;
    }

    void reColor(char* text)
    {

        if (getColor(text) == 1)
            setColor(text, 0);
        else
            setColor(text, 1);
    }

    void fixViolation(char* node)
    {
        setCheck = false;
        if (getColor(getParent(node)) == 0)
            return;

        else
        {

            if (getColor(findUncle(node)) == 1 && getColor(getParent(node)) == 1)
            {

                reColor(getParent(node));
                reColor(findUncle(node));

                if (!compareValues(grandparent(node), root))
                    reColor(grandparent(node));

                fixViolation(grandparent(node));

                // copyData(root, node);
            }
            else if (getColor(findUncle(node)) == 0 || findUncle(node) == NULL || compareValues(findUncle(node), "NULL"))
            {

                // setCheck = false;
                bool checkParentToChild = false;
                bool checkGrandParentToParent = false;
                char* resultant = new char[256];

                if (compareValues(getRightChild(getParent(node)), node))
                    checkParentToChild = true; // child is to right of parent
                else
                    checkParentToChild = false; // child is to the left of parent

                if (compareValues(getRightChild(grandparent(node)), getParent(node)))
                    checkGrandParentToParent = true;
                else
                    checkGrandParentToParent = false;

                if (!checkParentToChild && !checkGrandParentToParent)
                {
                    reColor(getParent(node));
                    reColor(grandparent(node));

                    copyData(resultant, rotateRight(grandparent(node)));
                }
                else if (checkParentToChild && checkGrandParentToParent)
                {
                    reColor(getParent(node));
                    reColor(grandparent(node));

                    copyData(resultant, rotateLeft(grandparent(node)));
                }
                else if (!checkGrandParentToParent && checkParentToChild)
                {
                    reColor(node);
                    reColor(grandparent(node));

                    char* dummyGrandParent = new char[256];
                    copyData(dummyGrandParent, grandparent(node));

                    setCheck = true;
                    setLeftChild(dummyGrandParent, rotateLeft(getLeftChild(grandparent(node))), setCheck);
                    setCheck = false;

                    copyData(resultant, rotateRight(dummyGrandParent));
                }
                else
                {

                    reColor(node);
                    reColor(grandparent(node));
                    char* dummyGrandParent = new char[256];
                    copyData(dummyGrandParent, grandparent(node));

                    setCheck = true;
                    setRightChild(dummyGrandParent, rotateRight(getRightChild(grandparent(node))), setCheck);
                    setCheck = false;

                    copyData(resultant, rotateLeft(dummyGrandParent));
                }

                if (compareValues(getParent(resultant), NULL))
                {
                    copyData(root, resultant);
                }

                char arr[256];
                int count = 0;

                // Copy cd into arr
                while (currentDir[count] != '\0')
                {
                    arr[count] = currentDir[count];
                    count++;
                }

                // Append "/root.txt" to the path
                arr[count++] = '/';
                arr[count++] = 'r';
                arr[count++] = 'o';
                arr[count++] = 'o';
                arr[count++] = 't';
                arr[count++] = '.';
                arr[count++] = 't';
                arr[count++] = 'x';
                arr[count++] = 't';
                arr[count] = '\0'; // Null-terminate the string

                // Create and write to "root.txt"
                std::ofstream object(arr);
                if (object.is_open())
                {
                    object << root;
                    object.close();
                }
                else
                {
                    std::cerr << "Failed to create file: " << arr << "\n";
                }
            }
        }
    }

    char* createfile(char* node, char* filename, char** values, int index, char* parent, int rowVal, bool lc_check, bool rc_check)
    {
        if (node == NULL)
        {
            char* newname = new char[256];

            if (compareValues(node, root))
            {
                newname = makeDefaultFile(filename, values, index, parent, rowVal, lc_check, rc_check, 0);
            }
            else
            {
                newname = makeDefaultFile(filename, values, index, parent, rowVal, lc_check, rc_check, 1);
            }

            if (root == NULL)
                copyData(root, newname);

            return newname;
        }

        int a = calHash(filename, rowVal);
        int b = getHash(node);

        if (a < b)
            setLeftChild(node, createfile(getLeftChild(node), filename, values, index, node, rowVal, 1, 0), setCheck);
        else if (a >= b)
            setRightChild(node, createfile(getRightChild(node), filename, values, index, node, rowVal, 0, 1), setCheck);

        // Fix Red-Black tree properties after insertion
        setHeight(node, 1 + max(height(getLeftChild(node)), height(getRightChild(node))));

        // char* finalRes = new char[256];
        // copyData(finalRes, fixViolation(filename));
        fixViolation(filename);
        // cout << "done with fix vio : " << endl;
        // return rebalance(filename);
    }

    void createfile(char* filename, char** values, int index, int rowVal)
    {
        setCheck = true;
        createfile(root, filename, values, index, NULL, rowVal, 0, 0);
        // cout << "root is : " << root << endl;
    }


};

class AVLTree
{
private:
    char* root;
    char* prev;
    char* currentDir;
    bool setBool = true;
public:
    AVLTree(char* cd)
    {
        root = NULL;
        prev = NULL;
        // Copy the directory path
        copyData(currentDir, cd);

        // Create the "root.txt" file
        char arr[256];
        int count = 0;

        // Copy cd into arr
        while (cd[count] != '\0')
        {
            arr[count] = cd[count];
            count++;
        }

        // Append "/root.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'r';
        arr[count++] = 'o';
        arr[count++] = 'o';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        // Create and write to "root.txt"
        std::ofstream object(arr);
        if (object.is_open())
        {
            object << "NULL";
            object.close();
        }
        else
        {
            std::cerr << "Failed to create file: " << arr << "\n";
        }

        // Reset arr and count for "commit.txt"
        count = 0;
        while (cd[count] != '\0')
        {
            arr[count] = cd[count];
            count++;
        }

        // Append "/commit.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'c';
        arr[count++] = 'o';
        arr[count++] = 'm';
        arr[count++] = 'm';
        arr[count++] = 'i';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        // Create and write to "commit.txt"
        std::ofstream object1(arr);
        if (object1.is_open())
        {
            object1.close();
        }
        else
        {
            std::cerr << "Failed to create file: " << arr << "\n";
        }
    }
    char* getRoot()
    {
        return root;
    }

    int calDataHash(char* line)
    {

        int i = 0;
        int final = 0;
        while (1)
        {
            if (line[i] == '\0')
                break;

            if (line[i] == ',')
            {
                i++;
                continue;
            }

            final += int(line[i]);
            i++;
        }
        return final;
    }

    void makeMerkel(const char* orgm, const char* newm, char* node, int& val, bool check)
    {

        if (getParent(node) == NULL)
        {
            if (!setBool)
                return;
            setBool = false;
            char* temp = new char[256];
            char* temp2 = new char[256];
            int i = 0;
            if (check)
            {

                while (orgm[i] != '\0')
                {
                    temp[i] = orgm[i];
                    temp2[i] = orgm[i];
                    i++;
                }
            }
            else
            {
                while (newm[i] != '\0')
                {
                    temp[i] = newm[i];
                    temp2[i] = orgm[i];
                    i++;
                }
            }

            int j = i;
            temp[i++] = '/';
            temp[i++] = 'r';
            temp[i++] = 'o';
            temp[i++] = 'o';
            temp[i++] = 't';
            temp[i++] = '.';
            temp[i++] = 't';
            temp[i++] = 'x';
            temp[i++] = 't';
            temp[i] = '\0';


            int l = 0;
            while (node[l] != '/')
                l++;
            while (node[l] != '\0') {
                temp2[j++] = node[l++];
            }
            temp2[j] = '\0';

            ofstream obj1;
            obj1.open(temp, ios::out);



            obj1 << temp2 << "\n";
            obj1.close();

            if (check)
                copyData(::n1, temp);
            else
                copyData(::n2, temp);
        }

        if (node == NULL)
            return;

        if (getLeftChild(node) == NULL && getRightChild(node) == NULL)
        {

            ifstream obj;
            obj.open(node, ios::in);
            char* linetemp = new char[1024];
            obj.getline(linetemp, 1024);
            int tmp = calDataHash(linetemp);
            val += tmp;
            obj.close();
        }
        else
        {
            int lv = 0;
            int rv = 0;
            makeMerkel(orgm, newm, getLeftChild(node), lv, check);
            makeMerkel(orgm, newm, getRightChild(node), rv, check);
            val = lv + rv;
        }

        ofstream obj2;
        char* newname = new char[256];
        int i = 0;
        if (check)
        {

            while (orgm[i] != '\0')
            {
                newname[i] = orgm[i];
                i++;
            }
        }
        else
        {
            while (newm[i] != '\0')
            {
                newname[i] = newm[i];
                i++;
            }
        }

        int j = 0;
        while (node[j] != '/')
        {
            j++;
        }

        while (node[j] != '\0')
        {
            newname[i++] = node[j++];
        }
        newname[i] = '\0';

        obj2.open(newname, ios::out);
        char* res = new char[50];
        intToCharArray(val, res);
        obj2 << res << "\n";
        if (getParent(node) == NULL)
            obj2 << "NULL\n";
        else
            obj2 << getParent(node) << "\n";

        if (getLeftChild(node) == NULL)
            obj2 << "NULL\n";
        else
            obj2 << getLeftChild(node) << "\n";

        if (getRightChild(node) == NULL)
            obj2 << "NULL\n";
        else
            obj2 << getRightChild(node) << "\n";

        obj2.close();

        /*if (getLeftChild(node) == NULL && getRightChild(node) == NULL) {
            makeMerkel(orgm, newm, getLeftChild(node), val, check);
            ::count--;
            makeMerkel(orgm, newm, getRightChild(node), val, check);
            ::count++;

            if (::count != 3)
            {
                ifstream obj;
                char* linetemp = new char[1024];
                obj.open(node, ios::in);
                obj.getline(linetemp, 1024);
                calDataHash(linetemp, val);
                obj.close();
            }

            if (::count == 3) {
                ofstream obj2;
                char* newname = new char[256];
                int i = 0;
                if (check) {

                    while (orgm[i] != '\0') {
                        newname[i] = orgm[i];
                        i++;
                    }
                }
                else {
                    while (newm[i] != '\0') {
                        newname[i] = newm[i];
                        i++;
                    }
                }

                int j = 0;
                while (node[j] != '/') {
                    j++;
                }

                while (node[j] != '\0') {
                    newname[i++] = node[j++];
                }
                newname[i] = '\0';


                obj2.open(newname, ios::out);
                char* res = new char[50];
                intToCharArray(temp, res);
                obj2 << res;
                obj2 << "\n";
                obj2.close();

                ::count = 0;
                temp = 0;
            }
            else
                temp += val;
        }
        else
            ::count--;*/
    }

    void callMerkel(const char* orgm, const char* newm, char* node)
    {

        bool check = false;
        if (fs::exists(orgm))
        {
            if (fs::exists(newm))
            {

                fs::rename(newm, orgm);
                if (fs::create_directory(fs::path(newm)))
                {
                    check = false;
                    cout << "Sub-Branch'" << newm << "' for Merkle Tree created successfully." << endl;
                }
            }
            else
            {

                if (fs::create_directory(fs::path(newm)))
                {
                    check = false;
                    cout << "Sub-Branch'" << newm << "' for Merkle Tree created successfully." << endl;
                }
            }
        }
        else
        {
            check = true;
            if (fs::create_directory(fs::path(orgm)))
            {
                cout << "Sub-Branch'" << orgm << "' for Merkle Tree created successfully." << endl;
            }
        }

        int val = 0;
        makeMerkel(orgm, newm, node, val, check);
        cout << "\nMerkle Tree Formed!" << endl;
    }

    bool compareHashVal(int a, int b)
    {
        if (a == b)
            return true;
        return false;
    }

    int calA(ifstream& obj1, char* line)
    {
        obj1.getline(line, 1024);
        int val = charArrayToInt(line);
        return val;
    }

    int calB(ifstream& obj2, char* line)
    {
        obj2.getline(line, 1024);
        int val = charArrayToInt(line);
        return val;
    }

    void callCompare(ifstream& obj1, ifstream& obj2, char* n1, char* n2, char*& temp, char* line)
    {

        if ((getRightChild(n1) == NULL && getLeftChild(n1) == NULL) || (getRightChild(n2) == NULL && getLeftChild(n2) == NULL))
            return;

        obj1.open(n1, ios::in);
        obj2.open(n2, ios::in);

        if (!(calA(obj1, line) != calA(obj2, line)))
        {
            copyData(temp, n1);
            obj1.close();
            obj2.close();
            return;
        }
        else
        {
            obj1.close();
            obj2.close();
            callCompare(obj1, obj2, getLeftChild(n1), getLeftChild(n2), temp, line);
            callCompare(obj1, obj2, getRightChild(n1), getRightChild(n2), temp, line);
        }
    }

    void comapreMerkle(const char* orgm, const char* newm)
    {

        ifstream obj1;
        ifstream obj2;

        char* temp;
        char* linetemp = new char[256];
        callCompare(obj1, obj2, ::n1, ::n2, temp, linetemp);
    }

    void inorder(char* node, int level)
    {

        if (node == NULL)
            return;

        preorder(getLeftChild(node), level + 1);
        for (int i = 0; i < level; i++)
            cout << "-";
        cout << ">";
        cout << node << endl;
        preorder(getRightChild(node), level + 1);
    }
    void callInorder(char* node)
    {
        cout << endl;
        inorder(node, 0);
        cout << endl;
    }

    void preorder(char* node, int level)
    {

        if (node == NULL)
            return;

        for (int i = 0; i < level; i++)
            cout << "-";
        cout << ">";
        cout << node << endl;

        preorder(getLeftChild(node), level + 1);
        preorder(getRightChild(node), level + 1);
    }
    void callPreorder(char* node)
    {
        cout << endl;
        preorder(node, 0);
        cout << endl;
    }

    void postorder(char* node, int level)
    {

        if (node == NULL)
            return;

        preorder(getLeftChild(node), level + 1);
        preorder(getRightChild(node), level + 1);
        for (int i = 0; i < level; i++)
            cout << "-";
        cout << ">";
        cout << node << endl;
    }
    void callPostorder(char* node)
    {
        cout << endl;
        postorder(node, 0);
        cout << endl;
    }

    int height(char* node)
    {

        if (node == NULL)
            return 0;

        ifstream obj;
        obj.open(node, ios::in);
        char* linetemp = new char[1024];
        getLineValue(obj, linetemp, 2);

        int a = charArrayToInt(linetemp);
        delete[] linetemp;
        return a;
    }

    int balanceFactor(char* node)
    {

        if (node != NULL)
            return (height(getLeftChild(node)) - height(getRightChild(node)));
        return 0;
    }

    /*bool balanced(char* node, bool& leftHeavy) {

        if (node != NULL)
        {
            bool ans = abs((height(getLeftChild(node)) - height(getRightChild(node)))) < 2;
            if (ans)
                return true;
            leftHeavy = (height(getLeftChild(node)) > height(getRightChild(node)));
        }

        return 0;
    }*/

    void copyData(char*& text, char* a)
    {
        text = new char[1024];
        int i = 0;
        while (a[i] != '\0')
        {
            text[i] = a[i];
            i++;
        }
        text[i] = '\0';
    }

    bool detectDirection(char* now, char* parent)
    {
        ifstream obj;
        char* leftVal = new char[256];
        obj.open(parent, ios::in);
        getLineValue(obj, leftVal, 5);
        obj.close();

        if (compareValues(now, leftVal))
        {
            delete[] leftVal;
            return false;
        }
        delete[] leftVal;
        return true;
    }
    char* rotateRight(char* now)
    {
        bool direction; // tells if the current now is left or right child of the parent.... false= left, true = right
        char* file1;
        copyData(file1, now);
        char* left = new char[256];
        char* rightOfLeft = new char[256];
        char* parent = new char[256];
        ifstream obj1;
        ifstream obj2;
        obj1.open(file1, ios::in);
        getLineValue(obj1, left, 5);
        obj1.clear();                 // Clear any error flags
        obj1.seekg(0, std::ios::beg); // Reset the pointer to the beginning of the file
        getLineValue(obj1, parent, 4);

        obj1.close();

        obj2.open(left, ios::in);
        getLineValue(obj2, rightOfLeft, 6);
        obj2.close();
        replace_line(file1, 5, rightOfLeft);
        replace_line(rightOfLeft, 4, file1);

        replace_line(left, 6, file1);
        replace_line(file1, 4, left);
        replace_line(left, 4, parent);

        if (!compareValues(parent, "NULL"))
        {
            direction = detectDirection(now, parent);

            if (direction)
                replace_line(parent, 6, left);
            else
                replace_line(parent, 5, left);
        }

        setHeight(file1, 1 + max(height(getLeftChild(file1)), height(getRightChild(file1))));
        setHeight(left, 1 + max(height(getLeftChild(left)), height(getRightChild(left))));
        setHeight(parent, 1 + max(height(getLeftChild(parent)), height(getRightChild(parent))));

        delete[] parent;
        delete[] rightOfLeft;
        return left;
    }

    char* rotateLeft(char* now)
    {
        bool direction; // tells if the current now is left or right child of the parent.... false= left, true = right
        char* file1;
        copyData(file1, now);
        char* right = new char[256];
        char* leftOfRight = new char[256];
        char* parent = new char[256];
        ifstream obj1;
        ifstream obj2;
        obj1.open(file1, ios::in);
        getLineValue(obj1, right, 6);
        obj1.clear();                 // Clear any error flags
        obj1.seekg(0, std::ios::beg); // Reset the pointer to the beginning of the file
        getLineValue(obj1, parent, 4);
        obj1.close();

        obj2.open(right, ios::in);
        getLineValue(obj2, leftOfRight, 5);
        obj2.close();
        replace_line(file1, 6, leftOfRight);
        replace_line(leftOfRight, 4, file1);

        // obj2.open(right, ios::in);
        replace_line(right, 5, file1);
        replace_line(file1, 4, right);
        replace_line(right, 4, parent);
        // obj2.close();

        if (!compareValues(parent, "NULL"))
        {
            direction = detectDirection(now, parent);

            if (direction)
                replace_line(parent, 6, right);
            else
                replace_line(parent, 5, right);
        }

        setHeight(file1, 1 + max(height(getLeftChild(file1)), height(getRightChild(file1))));
        setHeight(right, 1 + max(height(getLeftChild(right)), height(getRightChild(right))));
        setHeight(parent, 1 + max(height(getLeftChild(parent)), height(getRightChild(parent))));

        delete[] parent;
        delete[] leftOfRight;

        return right;
    }

    char* rebalance(char* node)
    {

        int bf = balanceFactor(node);
        if (bf > 1)
        {
            if (balanceFactor(getLeftChild(node)) < 0)
            {
                setLeftChild(node, rotateLeft(getLeftChild(node)));
            }
            return rotateRight(node);
        }
        else if (bf < -1)
        {
            if (balanceFactor(getRightChild(node)) > 0)
            {
                setRightChild(node, rotateRight(getRightChild(node)));
            }
            return rotateLeft(node);
        }

        return node;
    }
    int stringConverter(char* text)
    {
        int i = 0;
        int final = 1;
        while (text[i] != '/')
            i++;
        i++;
        while (text[i] != '.')
        {
            int tell = int(text[i]);
            final *= tell;
            i++;
        }

        return final;
    }

    int valConverter(char* text)
    {
        int i = 0;
        int final = 1;
        while (text[i] != '/')
            i++;
        i++;
        while (text[i] != '.')
        {
            int tell = text[i] - '0';
            final *= tell;
            i++;
        }

        return final;
    }

    char* valChecker(char* text, int rowVal)
    {
        int i = 0;
        bool check = false;
        while (text[i] != '/')
            i++;
        i++;
        while (text[i] != '.')
        {
            if (!(text[i] >= '0' && text[i] <= '9'))
            {
                check = true;
                break;
            }
            i++;
        }
        int finalVal = 0;
        if (check)
            finalVal = stringConverter(text);
        else
            finalVal = valConverter(text);

        //finalVal *= rowVal;
        finalVal = finalVal % 29;
        char* finalHash;
        intToCharArray(finalVal, finalHash);
        // cout << endl << "Hash: " << finalVal << endl;
        // cout << "Final Name: " << text << endl;
        return finalHash;
    }

    void intToCharArray(int num, char*& output)
    {
        // Find the number of digits in the integer
        int temp = num;
        int length = 0;
        bool isNegative = false;

        // Check if the number is negative
        if (num < 0)
        {
            isNegative = true;
            temp = -temp; // Make the number positive for digit counting
            length++;
        }

        // Count the digits
        do
        {
            length++;
            temp /= 10;
        } while (temp != 0);

        // Allocate memory for the char array
        output = new char[length + 1]; // +1 for the null terminator

        // If the number is negative, add the negative sign
        if (isNegative)
        {
            output[0] = '-';
        }

        // Convert the integer to char array
        int i = length - 1;
        temp = num < 0 ? -num : num; // Use the absolute value
        if (temp == 0)
        {
            output[i] = (0) + '0';
        }
        else
        {
            while (temp > 0)
            {
                output[i--] = (temp % 10) + '0'; // Convert digit to char
                temp /= 10;
            }
        }

        // Null terminate the string
        output[length] = '\0';
    }

    int charArrayToInt(const char* str)
    {
        int result = 0;
        bool isNegative = false;

        // Handle negative numbers
        if (str[0] == '-')
        {
            isNegative = true;
            str++; // Skip the negative sign
        }

        // Convert each character to its numeric value and accumulate
        for (int i = 0; str[i] != '\0'; ++i)
        {
            // Check if the character is a valid digit
            if (str[i] < '0' || str[i] > '9')
            {
                std::cerr << "Error: Invalid character in string" << std::endl;
                return 0; // Error case, invalid input
            }

            // Convert the character to an integer (digit) and add to result
            result = result * 10 + (str[i] - '0');
        }

        // If the number was negative, convert the result to negative
        if (isNegative)
        {
            result = -result;
        }

        return result;
    }

    void replace_line(char* parent, int line, const char* text)
    {

        ifstream obj1;
        ofstream obj2;

        obj1.open(parent, ios::in);
        obj2.open("temp.txt", ios::out | ios::trunc);

        // node parent change
        char* linetemp = new char[1024];
        int i = 0;
        obj1.getline(linetemp, 1024);
        while (linetemp[0] != '\0')
        {
            if (i != line - 1)
            {
                obj2 << linetemp;
                obj2 << "\n";
            }
            else
            {
                if (text == NULL)
                    obj2 << "NULL";
                else
                    obj2 << text;
                obj2 << "\n";
            }
            i++;
            obj1.getline(linetemp, 1024);
        }

        obj1.close();
        obj2.close();

        if (fs::exists(parent))
        {
            fs::remove(parent);
            // std::cout << "File deleted: " << parent << std::endl;
        }
        else
        {
            // std::cout << "File not found: " << parent << std::endl;
        }

        fs::rename("temp.txt", parent);
        delete[] linetemp;
    }

    char* makeDefaultFile(char* filename, char** values, int index, char* parent, int rowVal, bool lc_check, bool rc_check)
    {

        ofstream obj;
        obj.open(filename, std::ios::app);
        if (!obj.is_open())
        {
            std::cerr << "Failed to open or create file: " << filename << std::endl;
            return NULL;
        }

        // data copy
        if (values != NULL)
        {

            for (int i = 0; i <= index; i++)
                obj << values[i];
            obj << "\n";
        }
        else
            obj << "NULL\n";

        // height copy
        obj << "1\n";

        // hashcopy
        obj << valChecker(filename, rowVal);
        obj << "\n";

        // parent copy
        if (parent != NULL)
        {
            obj << parent;
            obj << "\n";
        }
        else
            obj << "NULL\n";

        // child 1 copy
        obj << "NULL\n";

        // child 2 copy
        obj << "NULL\n";

        obj.close();

        // if (parent != NULL) {
        //     if (lc_check) {
        //         replace_line(parent, 5, filename);
        //     }
        //     else if (rc_check) {
        //         replace_line(parent, 6, filename);
        //     }
        // }

        return filename;
        // cout << "\nalldone\n" << endl;
        // system("pause");
    }

    int getHash(const char* text)
    {
        ifstream obj;
        obj.open(text, ios::in);
        char* temptext = new char[1024];
        for (int i = 0; i < 3; i++)
            obj.getline(temptext, 1024);

        int val = charArrayToInt(temptext);
        obj.close();
        delete[] temptext;
        return val;
    }

    void getLineValue(ifstream& obj, char*& linetemp, int val)
    {

        for (int i = 0; i < val; i++)
            obj.getline(linetemp, 1024);
    }

    char* getLeftChild(const char* text)
    {
        ifstream obj;
        obj.open(text, ios::in);
        char* temptext = new char[1024];

        getLineValue(obj, temptext, 5);

        // char* finalleft = new char[256];
        char* finalleft;
        copyData(finalleft, temptext);
        delete[] temptext;
        obj.close();

        if (compareValues(finalleft, "NULL"))
            return NULL;
        return finalleft;
    }

    char* getRightChild(const char* text)
    {

        ifstream obj;
        obj.open(text, ios::in);
        char* temptext = new char[1024];
        getLineValue(obj, temptext, 6);

        // char* finalright = new char[256];
        char* finalright;
        copyData(finalright, temptext);
        delete[] temptext;
        obj.close();

        if (compareValues(finalright, "NULL"))
            return NULL;
        return finalright;
    }

    void setHeight(char* text, int val)
    {
        char* intChar;
        intToCharArray(val, intChar);
        replace_line(text, 2, intChar);
    }

    int calHash(char* node, int rowVal)
    {
        return charArrayToInt(valChecker(node, rowVal));
    }

    void setLeftChild(char* parent, char* lc)
    {
        replace_line(parent, 5, lc);
    }

    void setRightChild(char* parent, char* rc)
    {
        replace_line(parent, 6, rc);
    }

    char* createfile(char* node, char* filename, char** values, int index, char* parent, int rowVal, bool lc_check, bool rc_check)
    {
        if (node == NULL)
            return makeDefaultFile(filename, values, index, parent, rowVal, lc_check, rc_check);

        int a = calHash(filename, rowVal); // new file to be created
        int b = getHash(node);             // its parent

        if (a < b)
            setLeftChild(node, createfile(getLeftChild(node), filename, values, index, node, rowVal, 1, 0));
        // node = createfile(getLeftChild(node), filename, values, index, node, rowVal, 1, 0);
        else if (a >= b)
            setRightChild(node, createfile(getRightChild(node), filename, values, index, node, rowVal, 0, 1));
        // node = createfile(getRightChild(node), filename, values, index, node, rowVal, 0, 1);
        setHeight(node, 1 + max(height(getLeftChild(node)), height(getRightChild(node))));
        return rebalance(node);
    }

    void changeFilename(char* file, char*& root, bool choice, int rowVal)
    {

        char* newName = new char[256];
        copyData(newName, file);
        int i = 0;
        while (newName[i] != '.')
            i++;

        char* hashcal = new char[256];
        intToCharArray(rowVal, hashcal);
        int j = 0;
        while (hashcal[j] != '\0')
        {
            newName[i] = hashcal[j];
            i++;
            j++;
        }
        newName[i++] = '.';
        newName[i++] = 't';
        newName[i++] = 'x';
        newName[i++] = 't';
        newName[i] = '\0';

        fs::rename(file, newName);

        if (choice && root != NULL)
        {
            int i = 0;
            while (newName[i] != '\0')
            {
                root[i] = newName[i];
                i++;
            }
            root[i] = '\0';
        }
    }

    void createfile(char* filename, char** values, int index, int rowVal)
    {
        // if (compareValues(filename, root)) {
        //     changeFilename(filename, root, true, rowVal);
        // }
        // else
        //     changeFilename(filename, root, false, rowVal);

        copyData(root, createfile(root, filename, values, index, NULL, rowVal, 0, 0));

        char arr[256];
        int count = 0;

        // Copy cd into arr
        while (currentDir[count] != '\0')
        {
            arr[count] = currentDir[count];
            count++;
        }

        // Append "/root.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'r';
        arr[count++] = 'o';
        arr[count++] = 'o';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        // Create and write to "root.txt"
        std::ofstream object(arr);
        if (object.is_open())
        {
            object << root;
            object.close();
        }
        else
        {
            std::cerr << "Failed to create file: " << arr << "\n";
        }

        // cout << "rowval: " << rowVal << "  " << "filename: " << filename << endl;
        /*if (rowVal == 18) {
            cout << "masla : " << endl;
        }*/
        // cout << endl
        //<< "root is :" << root << endl;
        // system("pause");
    }

    int getCharPtrValue(const char* a)
    {
        int i = 0;
        while (a[i] != '\0')
            i++;
        return i;
    }

    bool compareValues(const char* a, const char* b)
    {
        if (a == NULL || b == NULL)
        {
            if (a == NULL && b == NULL)
                return true;
            return false;
        }

        if (getCharPtrValue(a) != getCharPtrValue(b))
            return false;
        else
        {
            int i = 0;
            while (a[i] != '\0')
            {
                if (a[i] != b[i])
                    return false;
                i++;
            }
            return true;
        }
    }

    char* getParent(const char* text)
    {
        if (text == NULL)
            return NULL;

        ifstream obj;
        obj.open(text, ios::in);
        char* temptext = new char[1024];

        getLineValue(obj, temptext, 4);

        char* finalval = new char[256];
        copyData(finalval, temptext);
        delete[] temptext;
        obj.close();

        if (compareValues(finalval, "NULL"))
            return NULL;
        return finalval;
    }

    char* removefile(int delHash, char* node, char* prev, bool lc, bool rc)
    {
        if (!node)
            return nullptr;

        if (delHash < getHash(node))
            setLeftChild(node, removefile(delHash, getLeftChild(node), node, true, false));
        else if (delHash > getHash(node))
            setRightChild(node, removefile(delHash, getRightChild(node), node, false, true));
        else if (delHash == getHash(node))
        {

            if (getLeftChild(node) == NULL && getRightChild(node) == NULL)
            {
                if (rc)
                    setRightChild(prev, NULL);
                else if (lc)
                    setLeftChild(prev, NULL);

                if (fs::exists(node))
                {
                    fs::remove(node);
                    cout << "file deleted" << endl;
                }
                else
                {
                    cout << "file not deleted" << endl;
                }

                return NULL;
            }
            else if (getLeftChild(node) == NULL || getRightChild(node) == NULL)
            {
                if (getLeftChild(node) != NULL)
                {

                    char* tempChild = new char[256];
                    copyData(tempChild, getLeftChild(node));

                    if (rc)
                    {
                        setRightChild(prev, getLeftChild(node));
                        replace_line(getLeftChild(node), 4, prev);
                    }
                    else if (lc)
                    {
                        setLeftChild(prev, getLeftChild(node));
                        replace_line(getLeftChild(node), 4, prev);
                    }

                    if (fs::exists(node))
                    {
                        fs::remove(node);
                        cout << "file deleted" << endl;
                    }
                    else
                    {
                        cout << "file not deleted" << endl;
                    }

                    return tempChild;
                }

                else if (getRightChild(node) != NULL)
                {

                    char* tempChild = new char[256];
                    copyData(tempChild, getRightChild(node));

                    if (rc)
                    {
                        setRightChild(prev, getRightChild(node));
                        replace_line(getRightChild(node), 4, prev);
                    }
                    else if (lc)
                    {
                        setLeftChild(prev, getRightChild(node));
                        replace_line(getRightChild(node), 4, prev);
                    }

                    if (fs::exists(node))
                    {
                        fs::remove(node);
                        cout << "file deleted" << endl;
                    }
                    else
                    {
                        cout << "file not deleted" << endl;
                    }

                    return tempChild;
                }
            }
            else if (getLeftChild(node) != NULL && getRightChild(node) != NULL)
            {

                char* temp1;
                copyData(temp1, getRightChild(node));
                char* prev;
                copyData(prev, node);
                char* kachra = getLeftChild(temp1);
                while (!(compareValues(getLeftChild(temp1), NULL)))
                {
                    copyData(prev, temp1);
                    copyData(temp1, getLeftChild(temp1));
                }

                char* dummyVal = new char[1024];
                if (compareValues(prev, node))
                {

                    setLeftChild(temp1, getLeftChild(node));
                    if (compareValues(getParent(node), NULL))
                        replace_line(temp1, 4, "NULL");
                    else
                        replace_line(temp1, 4, getParent(node));

                    replace_line(getLeftChild(node), 4, temp1);
                }
                else
                {
                    if (compareValues(getRightChild(temp1), NULL))
                        replace_line(prev, 5, "NULL");
                    else
                        replace_line(prev, 5, getRightChild(temp1));

                    if (compareValues(getParent(node), NULL))
                        replace_line(temp1, 4, "NULL");
                    else
                        replace_line(temp1, 4, getParent(node));

                    if (compareValues(getLeftChild(node), NULL))
                        replace_line(temp1, 5, "NULL");
                    else
                        replace_line(temp1, 5, getLeftChild(node));

                    if (compareValues(getRightChild(node), NULL))
                        replace_line(temp1, 6, "NULL");
                    else
                        replace_line(temp1, 6, getRightChild(node));
                }

                if (fs::exists(node))
                {
                    fs::remove(node);
                    cout << "file deleted" << endl;
                }
                else
                {
                    cout << "file not deleted" << endl;
                }

                copyData(node, temp1);
            }
        }
        setHeight(node, 1 + max(height(getLeftChild(node)), height(getRightChild(node))));
        return rebalance(node);
    }

    void removefile(char* filename)
    {
        prev = new char[256];
        copyData(root, removefile(getHash(filename), root, prev, false, false));
        delete[] prev;
    }
};

class BTree
{
    char* root;
    int order;
    bool updatec;
    int fileCounter;
    char* currentDir;

public:
    BTree(int order = 0, char* cd = NULL) : order(order)
    {
        fileCounter = 0;
        root = NULL;
        std::cout << "BTree created with order: " << order << "\n";

        // Copy the directory path
        copyData(currentDir, cd);

        // Create the "root.txt" file
        char arr[256];
        int count = 0;

        // Copy cd into arr
        while (cd[count] != '\0')
        {
            arr[count] = cd[count];
            count++;
        }

        // Append "/root.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'r';
        arr[count++] = 'o';
        arr[count++] = 'o';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        // Create and write to "root.txt"
        std::ofstream object(arr);
        if (object.is_open())
        {
            object << "NULL";
            object.close();
        }
        else
        {
            std::cerr << "Failed to create file: " << arr << "\n";
        }

        // Reset arr and count for "commit.txt"
        count = 0;
        while (cd[count] != '\0')
        {
            arr[count] = cd[count];
            count++;
        }

        // Append "/commit.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'c';
        arr[count++] = 'o';
        arr[count++] = 'm';
        arr[count++] = 'm';
        arr[count++] = 'i';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        // Create and write to "commit.txt"
        std::ofstream object1(arr);
        if (object1.is_open())
        {
            object1.close();
        }
        else
        {
            std::cerr << "Failed to create file: " << arr << "\n";
        }
    }

    // Creates a new file node and returns its pointer
    char* makeDefaultFile(char* filename, char** values, int index, char* parent, int rowVal, int order)
    {
        char* node = filename;
        int hash = calHash(filename, rowVal);

        // Initialize arrays for keys, hashes, and children
        std::ofstream file(filename);
        if (file.is_open())
        {
            // Initialize keys
            for (int i = 0; i < order; i++)
            {
                if (i == 0 && index > 0 && values != NULL)
                {
                    for (int i = 0; i <= index; i++)
                        file << values[i]; // Insert the given key
                }
                else
                {
                    file << "-1"; // Placeholder for unused keys
                }
                file << "\n"; // Separate keys with commas
            }

            // Initialize hashes
            for (int i = 0; i < order; i++)
            {
                if (i == 0)
                {
                    file << hash; // Insert hash for the given key
                }
                else
                {
                    file << "-1"; // Placeholder for unused hashes
                }
                file << "\n"; // Separate hashes with commas
            }
            // Add metadata: height and parent pointer
            file << "1\n";                              // Height of the new node
            file << (parent ? parent : "NULL") << "\n"; // Parent pointer

            // Initialize child pointers
            for (int i = 0; i < order + 1; i++)
            {
                file << "NULL"; // Placeholder for child pointers
                file << "\n";
            }

            file.close();
        }

        return node;
    }

    void createfile(char* filename, char** values, int index, int rowVal)
    {

        copyData(root, insert(root, filename, values, index, NULL, rowVal, order));

        char arr[256];
        int count = 0;

        // Copy cd into arr
        while (currentDir[count] != '\0')
        {
            arr[count] = currentDir[count];
            count++;
        }

        // Append "/root.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'r';
        arr[count++] = 'o';
        arr[count++] = 'o';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        // Create and write to "root.txt"
        std::ofstream object(arr);
        if (object.is_open())
        {
            object << root;
            object.close();
        }
        else
        {
            std::cerr << "Failed to create file: " << arr << "\n";
        }
        // system("pause");
    }

    char* insert(char* node, char* filename, char** values, int index, char* parent, int rowVal, int order)
    {
        if (node == nullptr)
        {
            // Create a new node file and return its filename
            return makeDefaultFile(filename, values, index, parent, rowVal, order);
        }

        // Retrieve keys and hashes from the current node
        char** keys = getKeysFromNode(node, order);
        int* hashes = getHash(node, order);
        int newHash = calHash(filename, rowVal);
        int height = getHeight(node);

        if (height > 1)
        {
            for (int i = 0; i < order; i++)
            {
                if (newHash < hashes[i] || hashes[i] == -1)
                {
                    char* temp = insert(getChildFromFile(node, i), filename, values, index, node, rowVal, order);
                    if (updatec)
                    {
                        setChildToFile(node, temp, i);
                    }
                    else
                    {
                        remove(temp);
                        updatec = 1;
                    }
                    updateParent(node);
                    keys = getKeysFromNode(node, order);
                    hashes = getHash(node, order);
                    break;
                }
            }
        }

        // Locate insertion index
        int i = 0;
        while (i < order - 1 && hashes[i] != -1 && newHash > hashes[i])
            i++;

        // Check if the current node is full
        bool isFull = hashes[order - 1] != -1;
        ;

        if (height == 1)
        {
            isFull = hashes[order - 2] != -1;
            // Insert directly into the current node
            for (int j = order - 1; j > i; j--)
            {
                keys[j] = keys[j - 1];
                hashes[j] = hashes[j - 1];
            }

            keys[i] = new char[256];
            int currentPos = 0; // To keep track of the position in keys[0]
            for (int k = 0; k < index; k++)
            {
                // Copy the current value from values[i] into keys[0]
                for (int j = 0; values[k][j] != '\0'; j++)
                {
                    keys[i][currentPos++] = values[k][j];
                }
            }
            keys[i][currentPos] = '\0';
            hashes[i] = newHash;

            for (int idx = 0; idx < order; ++idx)
            {
                if (keys[idx] != nullptr)
                {
                    setKeysToFile(node, keys[idx], idx);
                }
            }

            for (int idx = 0; idx < order; ++idx)
            {
                if (hashes[idx] != -1)
                {
                    setHashesToFile(node, hashes[idx], idx);
                }
            }

            updateNodeHeight(node, order);
            updatec = 1;
            if (!isFull)
                return node;
        }

        if (isFull)
        {
            // Node is full: Split
            node = splitNode(node, rowVal, order);
            updateParent(node);
            // If the parent exists, merge the median key of the current node with the parent
            if (parent != nullptr)
            {
                // Retrieve the median key and hash from the current node
                char* medianKey = getKeysFromNode(node, order)[0];
                int medianHash = getHash(node, order)[0];

                // Insert the median key and hash into the parent node
                char** parentKeys = getKeysFromNode(parent, order);
                int* parentHashes = getHash(parent, order);
                char** childs = getChildrenFromNode(parent, order);
                for (int i = 0; i < order + 1; i++)
                {
                    if (compareValues(childs[i], node))
                    {
                        delete[] childs[i];
                        for (int j = i + 1; j < order + 1; j++)
                        {
                            childs[j - 1] = childs[j];
                        }
                    }
                }

                int parentIndex = 0;
                while (parentIndex < order - 1 && parentHashes[parentIndex] != -1 && medianHash > parentHashes[parentIndex])
                {
                    parentIndex++;
                }

                // cout << "parentIndex: " << parentIndex << endl;
                //  Shift keys and hashes in the parent node to make space for the new entry
                for (int j = order - 1; j > parentIndex; j--)
                {
                    parentKeys[j] = parentKeys[j - 1];
                    parentHashes[j] = parentHashes[j - 1];
                }
                char* temp = childs[parentIndex];
                for (int i = order - 2; i >= parentIndex; i--)
                {
                    childs[i + 2] = childs[i];
                }

                // Insert the median key and hash into the parent
                parentKeys[parentIndex] = medianKey;
                parentHashes[parentIndex] = medianHash;
                childs[parentIndex] = getChildFromFile(node, 0);
                childs[parentIndex + 1] = getChildFromFile(node, 1);
                for (int i = 0; i < order; i++)
                {
                    setKeysToFile(parent, parentKeys[i], i);
                    setHashesToFile(parent, parentHashes[i], i);
                    setChildToFile(parent, childs[i], i);
                }
                setChildToFile(parent, childs[order], order);

                // setChildToFile(parent, getChildFromFile(node, 0), parentIndex);
                // setChildToFile(parent, getChildFromFile(node, 1), parentIndex+1);
                // system("pause");
                updatec = 0;
            }
        }

        // Update the parent's height
        updateNodeHeight(node, order);
        return node;
    }

    char* splitNode(char* node, int rowVal, int order)
    {
        // Determine the middle index for splitting
        int midIndex = (order - 1) / 2;

        // Retrieve keys and hashes from the current node
        char** keys = getKeysFromNode(node, order);
        int* hashes = getHash(node, order);

        // Create two new child nodes
        int leftHash = hashes[midIndex - 1];  // Hash for left child
        int rightHash = hashes[midIndex + 1]; // Hash for right child

        char* leftChild = getNameFromHash(leftHash, rowVal);   // Generate filename for left child
        char* rightChild = getNameFromHash(rightHash, rowVal); // Generate filename for right child

        // Initialize child files
        makeDefaultFile(leftChild, NULL, 0, node, 11, order);
        makeDefaultFile(rightChild, NULL, 0, node, 11, order);

        // Redistribute keys and hashes to left and right child nodes
        for (int i = 0; i < midIndex; ++i)
        {
            setKeysToFile(leftChild, keys[i], i);
            setHashesToFile(leftChild, hashes[i], i);
            setChildToFile(leftChild, getChildFromFile(node, i), i);
        }
        setChildToFile(leftChild, getChildFromFile(node, midIndex), midIndex);

        for (int i = midIndex + 1; i < order; ++i)
        {
            setKeysToFile(rightChild, keys[i], i - midIndex - 1);
            setHashesToFile(rightChild, hashes[i], i - midIndex - 1);
            setChildToFile(rightChild, getChildFromFile(node, i), i - midIndex - 1);
        }
        setChildToFile(rightChild, getChildFromFile(node, order), order - midIndex - 1);

        // Update the current node with the median key
        char* medianKey = keys[midIndex];
        setKeysToFile(node, medianKey, 0);
        for (int i = 1; i < order; ++i)
        {
            setKeysToFile(node, "-1", i); // Clear unused key slots
            setHashesToFile(node, -1, i); // Clear unused hash slots
        }

        // Update the child pointers in the current node
        setChildToFile(node, leftChild, 0);
        setChildToFile(node, rightChild, 1);
        for (int i = 2; i < order + 1; ++i)
        {
            setChildToFile(node, "NULL", i); // Clear unused child slots
        }

        // Update the heights of the child nodes
        updateNodeHeight(leftChild, order);
        updateNodeHeight(rightChild, order);

        // Return the updated current node
        return node;
    }

    void updateParent(char* node)
    {
        std::ifstream file(node);
        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << node << std::endl;
            return;
        }

        // Move to the child section of the file
        char* buffer = new char[1024];
        getLineValue(file, buffer, 2 * order + 2);

        for (int i = 0; i < order; i++)
        {
            file.getline(buffer, 1024);
            // Compare the entire buffer to "NULL"
            if (!compareValues(buffer, "NULL") == 0)
            {
                // Child is NULL, skip
                continue;
            }
            // Process non-NULL child here

            setParent(buffer, node);
        }
        file.close();
    }
    void updateNodeHeight(char* nodeFile, int order)
    {
        std::ifstream file(nodeFile);
        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << nodeFile << std::endl;
            return;
        }

        // Move to the child section of the file
        char* buffer = new char[1024];
        getLineValue(file, buffer, 2 * order + 2);

        int maxHeight = 0; // Initialize max height to 0
        for (int i = 0; i < order; i++)
        {
            file.getline(buffer, 1024);
            // Compare the entire buffer to "NULL"
            if (!compareValues(buffer, "NULL") == 0)
            {
                // Child is NULL, skip
                continue;
            }
            // Process non-NULL child here

            // Get the height of the child node
            std::ifstream childFile(buffer);
            if (!childFile.is_open())
            {
                std::cerr << "Error: Could not open child file " << buffer << std::endl;
                continue;
            }

            // Move to the height section of the child file
            for (int j = 0; j < 2 * order + 1; j++)
            {
                childFile.getline(buffer, 1024);
            }

            int childHeight = charArrayToInt(buffer);
            maxHeight = max(maxHeight, childHeight);

            childFile.close();
        }

        file.close();

        // Update the current node's height
        setHeight(nodeFile, maxHeight + 1); // Current node's height = max child height + 1
    }
    void replace_line(char* parent, int line, const char* text)
    {

        ifstream obj1;
        ofstream obj2;

        obj1.open(parent, ios::in);
        obj2.open("temp.txt", ios::out | ios::trunc);

        // node parent change
        char* linetemp = new char[1024];
        int i = 0;
        obj1.getline(linetemp, 1024);
        while (linetemp[0] != '\0')
        {
            if (i != line - 1)
            {
                obj2 << linetemp;
                obj2 << "\n";
            }
            else
            {
                obj2 << text;
                obj2 << "\n";
            }
            i++;
            obj1.getline(linetemp, 1024);
        }

        obj1.close();
        obj2.close();

        if (fs::exists(parent))
        {
            fs::remove(parent);
            // std::cout << "File deleted: " << parent << std::endl;
        }
        else
        {
            std::cout << "File not found: " << parent << std::endl;
        }

        fs::rename("temp.txt", parent);
    }

    void getLineValue(std::ifstream& obj, char*& linetemp, int val)
    {
        // Move to the desired line
        for (int i = 0; i < val; i++)
        {
            obj.getline(linetemp, 1024);
        }
    }
    char** getKeysFromNode(char* node, int order)
    {
        // Example: Read keys from the file and return as an array of strings (char**)
        int MAX_KEYS = order;
        char** keys = new char* [MAX_KEYS]; // Replace MAX_KEYS with your limit
        std::ifstream file(node);
        if (!file)
            return nullptr;

        for (int i = 0; i < MAX_KEYS; i++)
        {
            keys[i] = new char[256]; // Replace 256 with max key length
            file.getline(keys[i], 256);
        }

        file.close();
        return keys;
    }
    char** getChildrenFromNode(char* node, int order)
    {
        // Allocate memory for storing children
        int MAX_CHILDREN = order + 1;
        char** children = new char* [MAX_CHILDREN];
        for (int i = 0; i < MAX_CHILDREN; i++)
        {
            children[i] = new char[256]; // Assuming each child name can have a max length of 256
        }

        // Open the file for reading
        std::ifstream file(node);
        if (!file)
        {
            std::cerr << "Error: Could not open the file " << node << "\n";
            return nullptr;
        }

        // Use getLineValue to skip to the 5th line (children section starts here)
        char* buffer = new char[1024];
        getLineValue(file, buffer, 2 * order + 2); // Skips lines until the 5th line

        // Read child entries line by line
        for (int i = 0; i < MAX_CHILDREN; i++)
        {
            file.getline(children[i], 256); // Read each child line
            if (children[i][0] == '\0')
            {
                children[i][0] = '\0'; // Mark as empty if EOF or no data
                break;
            }
        }

        delete[] buffer;
        file.close();
        return children;
    }
    char* getNameFromHash(int hash, int rowVal)
    {
        // Convert the hash value to a string
        char* hashString = new char[16]; // Assuming hash values are small integers
        intToCharArray(hash, hashString);

        // Convert the rowVal value to a string
        char* rowValString = new char[16];
        intToCharArray(rowVal, rowValString);

        // Convert the counter value to a string
        char* counterString = new char[16];
        intToCharArray(fileCounter++, counterString); // Increment counter for each call

        // Generate the file name using the hash string, rowValString, and counterString
        const char* fileExtension = ".txt";

        // Calculate the total length of the file name
        int fileNameLength = strlen(currentDir) + 1 + strlen(hashString) + strlen(rowValString) + strlen(counterString) + strlen(fileExtension) + 1;

        // Allocate memory for the file name
        char* fileName = new char[fileNameLength];

        // Build the file name
        int pos = 0;

        // Manually copy the prefix
        for (int i = 0; currentDir[i] != '\0'; ++i)
        {
            fileName[pos++] = currentDir[i];
        }
        fileName[pos++] = '/';
        // Append the hash string
        for (int i = 0; hashString[i] != '\0'; ++i)
        {
            fileName[pos++] = hashString[i];
        }

        // Append the rowVal string
        for (int i = 0; rowValString[i] != '\0'; ++i)
        {
            fileName[pos++] = rowValString[i];
        }

        // Append the counter string
        for (int i = 0; counterString[i] != '\0'; ++i)
        {
            fileName[pos++] = counterString[i];
        }

        // Append the file extension
        for (int i = 0; fileExtension[i] != '\0'; ++i)
        {
            fileName[pos++] = fileExtension[i];
        }

        // Null-terminate the resulting string
        fileName[pos] = '\0';

        // Clean up allocated memory
        delete[] hashString;
        delete[] rowValString;
        delete[] counterString;

        return fileName;
    }
    int* getHash(const char* text, int order)
    {
        // Open the file in read mode
        std::ifstream obj(text);
        if (!obj.is_open())
        {
            std::cerr << "Error: Could not open file " << text << std::endl;
            return nullptr; // Error handling
        }

        // Skip the first two lines (keys section)
        char temptext[1024];
        for (int i = 0; i < order; i++)
        {
            obj.getline(temptext, 1024); // Skip key lines
        }

        // Read hashes section
        int* hashes = new int[order]; // Array to store hash values
        for (int i = 0; i < order; i++)
        {
            obj.getline(temptext, 1024);          // Read each hash value
            hashes[i] = charArrayToInt(temptext); // Convert to integer
        }

        obj.close();
        return hashes;
    }
    char* getChildFromFile(char* node, int index)
    {
        std::ifstream inFile(node);
        char* linetemp = new char[1024];
        int childStartLine = 2 * (order)+2; // Children section starts after keys, hashes, height, and parent
        int targetLine = index + childStartLine;

        while (inFile.good() && targetLine-- > 0)
        {
            getLineValue(inFile, linetemp, 1); // Move line by line
        }

        char* child = new char[1024];
        inFile.getline(child, 1024); // Read the child pointer
        inFile.close();
        return child;
    }
    int getHeight(char* node)
    {

        if (node == NULL)
            return 0;

        ifstream obj;
        obj.open(node, ios::in);
        char* linetemp = new char[1024];
        getLineValue(obj, linetemp, 2 * order + 1);

        return charArrayToInt(linetemp);
    }

    int calHash(char* node, int rowVal)
    {
        // Use valChecker to fetch the value associated with rowVal in the node
        char* value = valChecker(node, rowVal);
        if (value == nullptr)
        {
            std::cerr << "Error: Value for rowVal not found in node " << node << std::endl;
            return -1; // Error handling
        }

        // Convert the fetched value to an integer (hash calculation)
        int hashValue = charArrayToInt(value);

        delete[] value; // Free dynamically allocated memory from valChecker
        return hashValue;
    }
    void copyData(char*& dest, const char* src)
    {
        int length = 0;
        while (src[length] != '\0')
            ++length;

        dest = new char[length + 1];
        for (int i = 0; i < length; ++i)
        {
            dest[i] = src[i];
        }
        dest[length] = '\0'; // Null-terminate the destination
    }
    bool compareValues(const char* a, const char* b)
    {
        int i = 0;
        while (a[i] != '\0' && b[i] != '\0')
        {
            if (a[i] != b[i])
                return false;
            ++i;
        }
        return a[i] == '\0' && b[i] == '\0';
    }

    void setKeysToFile(char* node, const char* key, int index)
    {
        std::ifstream inFile(node);
        std::ofstream outFile("temp.txt");
        char* linetemp = new char[1024];
        int currentLine = 0;

        while (inFile.good())
        {
            getLineValue(inFile, linetemp, 1); // Move line by line
            if (currentLine == index)
            {
                outFile << key << endl; // Replace the line with the new key
            }
            else
            {
                outFile << linetemp << "\n"; // Copy other lines as is
            }
            currentLine++;
        }

        delete[] linetemp;
        inFile.close();
        outFile.close();

        // Replace original file with updated file
        std::remove(node);
        std::rename("temp.txt", node);
    }
    void setHashesToFile(char* node, int hash, int index)
    {
        std::ifstream inFile(node);
        std::ofstream outFile("temp.txt");
        char* linetemp = new char[1024];
        int currentLine = 0;
        int hashStartLine = order; // Hash section starts after keys

        while (inFile.good())
        {
            getLineValue(inFile, linetemp, 1); // Move line by line
            if (currentLine == index + hashStartLine)
            {
                char* hashStr = new char[12];
                intToCharArray(hash, hashStr);
                outFile << hashStr << "\n"; // Replace the line with the new hash
            }
            else
            {
                outFile << linetemp << "\n"; // Copy other lines as is
            }
            currentLine++;
        }

        delete[] linetemp;
        inFile.close();
        outFile.close();

        // Replace original file with updated file
        std::remove(node);
        std::rename("temp.txt", node);
    }
    void setChildToFile(char* node, const char* child, int index)
    {
        std::ifstream inFile(node);
        std::ofstream outFile("temp.txt");
        char* linetemp = new char[1024];
        int currentLine = 0;
        int childStartLine = 2 * (order)+2; // Children section starts after keys, hashes, height, and parent

        while (inFile.good())
        {
            getLineValue(inFile, linetemp, 1); // Move line by line
            if (currentLine == index + childStartLine)
            {
                outFile << child << "\n"; // Replace the line with the new child pointer
            }
            else
            {
                outFile << linetemp << "\n"; // Copy other lines as is
            }
            currentLine++;
            if (currentLine >= 3 * order + 3)
                break;
        }

        delete[] linetemp;
        inFile.close();
        outFile.close();

        // Replace original file with updated file
        std::remove(node);
        std::rename("temp.txt", node);
    }
    void setHeight(char* text, int h)
    {
        char* intChar;
        intToCharArray(h, intChar);
        replace_line(text, 2 * order + 1, intChar);
    }
    void setParent(char* text, const char* parent)
    {
        replace_line(text, 2 * order + 2, parent);
    }

    void intToCharArray(int num, char*& output)
    {
        // Find the number of digits in the integer
        int temp = num;
        int length = 0;
        bool isNegative = false;

        // Check if the number is negative
        if (num < 0)
        {
            isNegative = true;
            temp = -temp; // Make the number positive for digit counting
            length++;
        }

        // Count the digits
        do
        {
            length++;
            temp /= 10;
        } while (temp != 0);

        // Allocate memory for the char array
        output = new char[length + 1]; // +1 for the null terminator

        // If the number is negative, add the negative sign
        if (isNegative)
        {
            output[0] = '-';
        }

        // Convert the integer to char array
        int i = length - 1;
        temp = num < 0 ? -num : num; // Use the absolute value
        if (temp == 0)
        {
            output[i] = (0) + '0';
        }
        else
        {
            while (temp > 0)
            {
                output[i--] = (temp % 10) + '0'; // Convert digit to char
                temp /= 10;
            }
        }

        // Null terminate the string
        output[length] = '\0';
    }
    int charArrayToInt(const char* str)
    {
        int result = 0;
        bool isNegative = false;

        // Handle negative numbers
        if (str[0] == '-')
        {
            isNegative = true;
            str++; // Skip the negative sign
        }

        // Convert each character to its numeric value and accumulate
        for (int i = 0; str[i] != '\0'; ++i)
        {
            // Check if the character is a valid digit
            if (str[i] < '0' || str[i] > '9')
            {
                std::cerr << "Error: Invalid character in string" << std::endl;
                return 0; // Error case, invalid input
            }

            // Convert the character to an integer (digit) and add to result
            result = result * 10 + (str[i] - '0');
        }

        // If the number was negative, convert the result to negative
        if (isNegative)
        {
            result = -result;
        }

        return result;
    }
    int valConverter(char* text)
    {
        int i = 0;
        int final = 1;
        while (text[i] != '/')
            i++;
        i++;
        while (text[i] != '.')
        {
            int tell = text[i] - '0';
            final *= tell;
            i++;
        }

        return final;
    }
    char* valChecker(char* text, int rowVal)
    {
        int i = 0;
        bool check = false;
        while (text[i] != '/')
            i++;
        i++;
        while (text[i] != '.')
        {
            if (!(text[i] >= '0' && text[i] <= '9'))
            {
                check = true;
                break;
            }
            i++;
        }
        int finalVal = 0;
        if (check)
            finalVal = stringConverter(text);
        else
            finalVal = valConverter(text);

        if (!finalVal)
        {
            srand(time(NULL)); // Seed the random number generator
            finalVal = rand(); // Generate a random number
            finalVal = finalVal % 5000;
        }

        finalVal *= rowVal;
        finalVal = finalVal % 29;
        char* finalHash;
        intToCharArray(finalVal, finalHash);

        return finalHash;
    }
    int stringConverter(char* text)
    {
        int i = 0;
        int final = 1;
        while (text[i] != '/')
            i++;
        i++;
        while (text[i] != '.')
        {
            int tell = int(text[i]);
            final *= tell;
            i++;
        }

        return final;
    }
};

char* createVersion(char* currentDir, int cc)
{

    fs::path sourceDir; // Specify the source directory
    fs::path destDir;   // Specify the destination directory

    sourceDir = currentDir; // Specify the source directory
    char* dest = new char[50];
    int i = 0;
    while (currentDir[i] != '\0')
    {
        dest[i] = currentDir[i];
        i++;
    }

    dest[i++] = '_';
    int m = cc % 10;
    switch (m)
    {
    case 0:
        dest[i++] = '0';
        break;
    case 1:
        dest[i++] = '1';
        break;
    case 2:
        dest[i++] = '2';
        break;
    case 3:
        dest[i++] = '3';
        break;
    case 4:
        dest[i++] = '4';
        break;
    case 5:
        dest[i++] = '5';
        break;
    case 6:
        dest[i++] = '6';
        break;
    case 7:
        dest[i++] = '7';
        break;
    case 8:
        dest[i++] = '8';
        break;
    case 9:
        dest[i++] = '9';
        break;
    }
    if (cc > 9)
    {
        cc /= 10;
        m = cc % 10;
        switch (m)
        {
        case 0:
            dest[i++] = '0';
            break;
        case 1:
            dest[i++] = '1';
            break;
        case 2:
            dest[i++] = '2';
            break;
        case 3:
            dest[i++] = '3';
            break;
        case 4:
            dest[i++] = '4';
            break;
        case 5:
            dest[i++] = '5';
            break;
        case 6:
            dest[i++] = '6';
            break;
        case 7:
            dest[i++] = '7';
            break;
        case 8:
            dest[i++] = '8';
            break;
        case 9:
            dest[i++] = '9';
            break;
        }
    }
    dest[i] = '\0';

    destDir = dest; // Specify the destination directory

    /*if (fs::create_directory(destDir)) {
        cout << "Branch '" << currentDir << "' created Successfully!" << endl;

    }
    else
    {
        std::cout << "Failed to create destination directory.\n";

    }*/
    // Copy directory recursively
    fs::copy(sourceDir, destDir, fs::copy_options::recursive);
    return dest;
    // std::cout << "Directory copied successfully from '" << sourceDir << "' to '" << destDir << "'.\n";
}
bool compareValues(const char* a, const char* b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
            return false;
        ++i;
    }
    return a[i] == '\0' && b[i] == '\0';
}
void copyData(char*& text, char* a)
{
    text = new char[1024];
    int i = 0;
    while (a[i] != '\0')
    {
        text[i] = a[i];
        i++;
    }
    text[i] = '\0';
}

void getLineValue(std::ifstream& obj, char*& linetemp, int val)
{
    // Move to the desired line
    for (int i = 0; i < val; i++)
    {
        obj.getline(linetemp, 1024);
    }
}
char* generateTree(char* branchname, int& tc, AVLTree*& obj1, BTree*& obj2, RBTree*& obj3)
{
    char* dataset = new char[50];
    char* line = new char[1024];
    char* firstLine = new char[1024];
    int startRow = 0;
    int endRow = 0;

    while (1)
    {
        cout << "Enter the dataset address for Tree generation: ";
        cin.ignore();
        cin.clear();
        cin.getline(dataset, 256);
        //cin >> dataset;
        cout << "\nEnter the start range of reading CSV file: ";
        cin >> startRow;
        cout << "\nEnter the end range of reading CSV file: ";
        while (1)
        {
            cin >> endRow;
            if (endRow <= startRow)
                cout << "Incorrect choice\n ";
            else
                break;
        }
        ifstream file(dataset);

        if (file.is_open())
        {
            char** values = new char* [100];
            for (int i = 0; i < 100; i++)
            {
                values[i] = new char[256];
            }

            char* filename = new char[1024];
            file.getline(line, 1024);

            cout << endl;
            int col = -1;
            copyData(firstLine, line);
            cout << "The Column Are : " << endl
                << line << endl
                << endl
                << endl;
            cout << "Enter Column Number : ";
            cin >> col;
            cout << endl;

            int treeChoice = -1;
            int oorder = 0;
            cout << "Select your desired tree : \n";
            cout << "AVL Tree --> Press '1' \n";
            cout << "B Tree --> Press '2' \n";
            cout << "Red-Black Tree --> Press '3' \n\n";
            cout << "Enter : ";
            cin >> treeChoice;
            cout << "\n--------------------------------------------------------------------------------------------------------------------\n\n";

            tc = treeChoice;
            switch (treeChoice)
            {
            case 1:
                obj1 = new AVLTree(branchname);
                break;

            case 2:
                cout << endl
                    << "Order of B Tree --> ";
                cin >> oorder;
                obj2 = new BTree(oorder, branchname);
                break;

            case 3:
                obj3 = new RBTree(branchname);
                break;
            }

            for (int i = 0; i < startRow; i++)
            {
                file.getline(line, 1024);
            }
            int rowVal = startRow;

            while (rowVal < endRow)
            {
                file.getline(line, 1024);
                if (line[0] == '\0')
                    break;
                int currentIndex = 0;
                int wordIndex = 0;
                int charIndex = 0;
                int filenameIndex = 0;
                bool fileCheck = false;
                char* dummy = new char[256];

                int i = 0;
                while (branchname[i] != '\0')
                {
                    filename[filenameIndex++] = branchname[i++];
                }
                filename[filenameIndex++] = '/';

                while (line[currentIndex] != '\0')
                {

                    if (line[currentIndex] == ',')
                    {
                        if (fileCheck)
                        {
                            if (treeChoice == 1)
                                obj1->intToCharArray(rowVal, dummy);
                            else if (treeChoice == 2)
                                obj2->intToCharArray(rowVal, dummy);
                            else if (treeChoice == 3)
                                obj3->intToCharArray(rowVal, dummy);
                            //int dum = 0;
                            //while (dummy[dum] != '\0')
                            //{
                            //    filename[filenameIndex++] = dummy[dum++];
                            //}
                            filename[filenameIndex++] = '.';
                            filename[filenameIndex++] = 't';
                            filename[filenameIndex++] = 'x';
                            filename[filenameIndex++] = 't';
                            filename[filenameIndex] = '\0';
                            filenameIndex = 0;
                            fileCheck = false;
                        }

                        currentIndex++;
                        values[wordIndex][charIndex++] = ',';
                        values[wordIndex][charIndex] = '\0';
                        wordIndex++;
                        charIndex = 0;
                    }
                    if (wordIndex == col)
                    {
                        if (line[currentIndex] != ' ')
                        {
                            filename[filenameIndex++] = line[currentIndex];
                        }
                        fileCheck = true;
                    }

                    /*if (filenameIndex >= 1024) {
                        throw std::runtime_error("Exceeded filename buffer.");
                    }

                    if (charIndex >= 256) {
                        throw std::runtime_error("Exceeded row size in values.");
                    }*/

                    values[wordIndex][charIndex++] = line[currentIndex++];
                    if (line[currentIndex] == '\0')
                        values[wordIndex][charIndex] = '\0';
                }
                // Rest of the code remains the same as AVL tree implementation
                // ... (copy the existing row processing logic from AVL tree)

                if (treeChoice == 1)
                    obj1->createfile(filename, values, wordIndex, rowVal);
                else if (treeChoice == 2)
                    obj2->createfile(filename, values, wordIndex, rowVal);
                else if (treeChoice == 3)
                    obj3->createfile(filename, values, wordIndex, rowVal);

                rowVal++;
                cout << "\nRow: " << rowVal << endl;
                // system("pause");
            }
            cout << "\nTREE CREATED SUCCESSFULLY!\n";
            cout << "\n--------------------------------------------------------------------------------------------------------------------\n\n";

            break;
        }
        else
            cout << "CSV File Openeing Error!\n";
    }

    return firstLine;
}
void getColumnValue(const char* line, int columnIndex, char*& columnValue, int maxLength)
{
    int currentColumn = 0, i = 0, j = 0;
    while (line[i] != '\0' && j < maxLength - 1)
    {
        if (line[i] == ',')
        {
            ++currentColumn;
            ++i;
            continue;
        }
        if (currentColumn == columnIndex)
        {
            columnValue[j++] = line[i];
        }
        ++i;
    }
    columnValue[j] = '\0'; // Null-terminate the extracted column
}

void setColumnValue(char*& line, int columnIndex, const char* newValue, int maxLength)
{
    char updatedLine[256]; // Temporary array to store the updated line
    int currentColumn = 0, i = 0, j = 0, k = 0;

    while (line[i] != '\0' && j < maxLength - 1)
    {
        // Check if we are at the target column
        if (currentColumn == columnIndex)
        {
            // Append the new value to the updated line
            updatedLine[j++] = ',';
            i++;
            while (newValue[k] != '\0' && j < maxLength - 1)
            {
                updatedLine[j++] = newValue[k++];
            }

            // Skip the old value in the target column
            while (line[i] != ',' && line[i] != '\0')
            {
                ++i;
            }

            // If a comma exists after the column, include it
            if (line[i] == ',')
            {
                updatedLine[j++] = line[i++];
            }

            // Move to the next column
            currentColumn++;
        }

        // If not at the target column, copy characters from the original line
        else
        {
            updatedLine[j++] = line[i++];
            if (line[i] == ',')
            {
                currentColumn++;
            }
        }
    }

    // Null-terminate the updated line
    updatedLine[j] = '\0';

    // Copy the updated line back to the original line
    for (i = 0; updatedLine[i] != '\0'; ++i)
    {
        line[i] = updatedLine[i];
    }
    line[i] = '\0'; // Null-terminate the original line
}

void replace_line(char* parent, int line, const char* text)
{

    ifstream obj1;
    ofstream obj2;

    obj1.open(parent, ios::in);
    obj2.open("temp.txt", ios::out | ios::trunc);

    // node parent change
    char* linetemp = new char[1024];
    int i = 0;
    obj1.getline(linetemp, 1024);
    while (linetemp[0] != '\0')
    {
        if (i != line - 1)
        {
            obj2 << linetemp;
            obj2 << "\n";
        }
        else
        {
            obj2 << text;
            obj2 << "\n";
        }
        i++;
        obj1.getline(linetemp, 1024);
    }

    obj1.close();
    obj2.close();

    if (fs::exists(parent))
    {
        fs::remove(parent);
        // std::cout << "File deleted: " << parent << std::endl;
    }
    else
    {
        std::cout << "File not found: " << parent << std::endl;
    }

    fs::rename("temp.txt", parent);
}
void appendLineToTop(const char* fileName, const char* lineToAdd)
{
    // Open the file in read mode
    std::ifstream fileIn(fileName, std::ios::in);
    if (!fileIn)
    {
        std::cerr << "Error: Could not open file for reading: " << fileName << std::endl;
        return;
    }

    // Determine file size
    fileIn.seekg(0, std::ios::end);
    int fileSize = fileIn.tellg();
    fileIn.seekg(0, std::ios::beg);

    // Allocate memory for the file content
    char* fileContent = nullptr;
    if (fileSize > 0)
    {
        fileContent = new char[fileSize];
        fileIn.read(fileContent, fileSize);
    }

    fileIn.close();

    // Open the file in write mode
    std::ofstream fileOut(fileName, std::ios::out);
    if (!fileOut)
    {
        std::cerr << "Error: Could not open file for writing: " << fileName << std::endl;
        delete[] fileContent;
        return;
    }

    // Write the new line manually
    for (int i = 0; lineToAdd[i] != '\0'; i++)
    {
        fileOut << lineToAdd[i];
    }
    fileOut << '\n';

    // Write the original content back to the file
    if (fileContent)
    {
        for (int i = 0; i < fileSize; ++i)
        {
            fileOut << fileContent[i];
        }
    }

    // Clean up
    delete[] fileContent;
    fileOut.close();
}
void traverseAndUpdateTree(char* root, char* toUpdate, char* updateAgainst, int columnIndex)
{
    // Array to store the first line of the file
    char* firstLine = new char[1024];
    char* columnValue = new char[1024];
    char* leftChild = new char[1024];
    char* rightChild = new char[1024];

    // Get the first line of the file
    ifstream obj;
    obj.open(root, ios::in);
    getLineValue(obj, firstLine, 1);
    getLineValue(obj, leftChild, 4);
    getLineValue(obj, rightChild, 1);
    obj.close();

    // cout << "firstline is " << firstLine<<endl<< "leftchild is " << leftChild << " and right child is " << rightChild << endl;
    //  Extract the column value
    getColumnValue(firstLine, columnIndex, columnValue, 256);

    // Check if the value matches `updateAgainst`
    int i = 0;
    bool isEqual = compareValues(columnValue, updateAgainst);

    // If they match, update the value
    if (isEqual)
    {
        setColumnValue(firstLine, columnIndex, toUpdate, 256);
        replace_line(root, 1, firstLine);
    }

    // Recursively traverse the left child
    if (leftChild[0] != 'N' || leftChild[1] != 'U' || leftChild[2] != 'L' || leftChild[3] != 'L')
    { // Skip NULL children
        traverseAndUpdateTree(leftChild, toUpdate, updateAgainst, columnIndex);
    }

    // Recursively traverse the right child
    if (rightChild[0] != 'N' || rightChild[1] != 'U' || rightChild[2] != 'L' || rightChild[3] != 'L')
    { // Skip NULL children
        traverseAndUpdateTree(rightChild, toUpdate, updateAgainst, columnIndex);
    }

    // Clean up dynamically allocated memory
    delete[] firstLine;
    delete[] columnValue;
    delete[] leftChild;
    delete[] rightChild;
}

void commit(char*& currentDir, char* firstLine, int cc, AVLTree*& obj1)
{
    system("cls");

    int in;
    int col;
    char* toUpdate = new char[256];
    char* filename = new char[1024];
    char* dir = new char[256];
    char* message = new char[1024];
    int th = 0;
    int count = 0;
    char* lol = new char[50];
    char* arr = new char[30];


    cout << "\nChoose from the following commands:\n    1. >update specific file\n    2. >update in all files\n    3. >Delete File\n    4.>Insert File\n   5. >Exit\n";
    cin >> in;

    cout << "Enter Branch: ";
    cin.clear();
    cin.ignore();
    cin.getline(dir, 1024);
    if (!compareValues(dir, currentDir))
    {
        cout << "We are currently in branch \"" << currentDir << "\", so kindly switch your branch first" << endl;
        return;
    }

    cout << "\nMaking version\n";
    cout << "Current dir: " << currentDir << endl;

    system("pause");
    copyData(dir, createVersion(currentDir, cc));
    copyData(currentDir, dir);

    cout << "\nafter: " << currentDir << endl;

    switch (in)
    {
    case 1:

        // cout << "currentDirectory: " << currentDir<<endl;

    {
        cout << "Enter File Name: ";
        cin >> filename;

        cout << "The Column Are : " << endl
            << firstLine << endl;
        cout << "Enter Column Number : ";
        cin >> col;

        cout << "Enter Updated Value: ";
        cin.clear();
        cin.ignore();
        cin.getline(toUpdate, 1024);

        cout << "Enter Commit Message: ";
        cin.clear();
        cin.getline(message, 1024);

        int index = 0;

        while (dir[index] != '\0')
        {
            index++;
        }
        dir[index++] = '/';

        int fileIndex = 0;
        while (filename[fileIndex] != '\0')
        {
            dir[index++] = filename[fileIndex++];
        }
        dir[index] = '\0';

        std::ifstream obj(dir, std::ios::in);
        if (!obj.is_open())
        {
            std::cerr << "Error: Unable to open file at path " << dir << "\n";
            return;
        }

        getLineValue(obj, filename, 1);
        obj.close();

        setColumnValue(filename, col, toUpdate, 1024);

        replace_line(dir, 1, filename);



        while (currentDir[count] != '\0')
        {
            arr[count] = currentDir[count];
            count++;
        }
        // Append "/commit.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'c';
        arr[count++] = 'o';
        arr[count++] = 'm';
        arr[count++] = 'm';
        arr[count++] = 'i';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        appendLineToTop(arr, message);
    }

    break;

    case 2:

    {
        cout << "The Column Are : " << endl
            << firstLine << endl;
        cout << "Enter Column Number : ";
        cin >> col;

        cout << "Enter Value to Replace: ";
        cin >> filename;

        cout << "Enter Updated Value: ";
        cin.clear();
        cin.ignore();
        cin.getline(toUpdate, 1024);

        cout << "Enter Commit Message: ";
        cin.clear();
        cin.getline(message, 1024);

        int count = 0;
        char* arr = new char[30];
        while (currentDir[count] != '\0')
        {
            arr[count] = currentDir[count];
            count++;
        }
        // Append "/commit.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'r';
        arr[count++] = 'o';
        arr[count++] = 'o';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        std::ifstream obj(arr, std::ios::in);
        if (!obj.is_open())
        {
            std::cerr << "Error: Unable to open file at path " << dir << "\n";
            return;
        }
        getLineValue(obj, dir, 1);
        obj.close();

        traverseAndUpdateTree(dir, toUpdate, filename, col);

        count = 0;
        while (currentDir[count] != '\0')
        {
            arr[count] = currentDir[count];
            count++;
        }
        // Append "/commit.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'c';
        arr[count++] = 'o';
        arr[count++] = 'm';
        arr[count++] = 'm';
        arr[count++] = 'i';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        appendLineToTop(arr, message);
    }

    break;
    case 3:


        cout << "Enter the file name you want to delete: ";
        cin >> lol;


        while (currentDir[count] != '\0')
        {
            arr[count] = currentDir[count];
            count++;
        }
        arr[count++] = '/';
        th = 0;
        while (lol[th] != '\0') {
            arr[count++] = lol[th];
            th++;
        }
        arr[count++] = '\0';

        obj1->removefile(arr);
        break;

    case 5:
        return;
    }
}
void commitHistory(char* currentDir) {
    // Construct the path to commit.txt
    char* filePath = new char[256];
    int i = 0;
    while (currentDir[i] != '\0') {
        filePath[i] = currentDir[i];
        i++;
    }
    filePath[i++] = '/';
    filePath[i++] = 'c';
    filePath[i++] = 'o';
    filePath[i++] = 'm';
    filePath[i++] = 'm';
    filePath[i++] = 'i';
    filePath[i++] = 't';
    filePath[i++] = '.';
    filePath[i++] = 't';
    filePath[i++] = 'x';
    filePath[i++] = 't';
    filePath[i] = '\0';

    // Open the file
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open commit file at " << filePath << "\n";
        delete[] filePath;
        return;
    }

    // Read all lines into a buffer
    char** lines = new char* [100]; // Assuming at most 100 lines
    int lineCount = 0;

    char buffer[256];
    while (file.getline(buffer, 256)) {
        lines[lineCount] = new char[256];
        int j = 0;
        while (buffer[j] != '\0') {
            lines[lineCount][j] = buffer[j];
            j++;
        }
        lines[lineCount][j] = '\0';
        lineCount++;
    }

    file.close();

    // Display the lines in reverse order
    for (int k = lineCount - 1; k >= 0; --k) {
        std::cout << "commit " << (lineCount - k) << ": " << lines[k] << "\n";
        delete[] lines[k]; // Clean up each line
    }

    // Clean up remaining allocated memory
    delete[] lines;
    delete[] filePath;
}
int main()
{
    const int boxWidth = 120; // Width of the box
    const int boxHeight = 29; // Height of the box

    // Set console text color (e.g., bright yellow)
    setConsoleColor(14);

    // Top border
    printLine(boxWidth, '+', '-', '+');

    // Middle lines
    for (int i = 1; i < boxHeight - 1; ++i)
    {
        if (i == boxHeight / 2)
        { // Centered line for the welcome message
            std::cout << '|';
            int padding = (boxWidth - 22) / 2; // Calculate padding (22 is the message length)
            for (int j = 0; j < padding; ++j)
                std::cout << ' ';
            std::cout << "WELCOME TO GITLite  ";
            for (int j = 0; j < padding; ++j)
                std::cout << ' ';
            std::cout << '|' << std::endl;
        }
        else
        {
            std::cout << '|';
            for (int j = 1; j < boxWidth - 1; ++j)
            {
                std::cout << ' ';
            }
            std::cout << '|' << std::endl;
        }
    }

    // Bottom border
    printLine(boxWidth, '+', '-', '+');

    // Reset color to default
    setConsoleColor(7);

    system("pause");
    system("cls");

    char** folderNames = new char* [10];
    for (int i = 0; i < 10; i++)
    {
        folderNames[i] = new char[50];
    }
    int folderCount = 0;

    AVLTree* obj1 = NULL;
    BTree* obj2 = NULL;
    RBTree* obj3 = NULL;
    int treeChoice = 0;
    char* currentDir = new char[256];
    char* firstLine = new char[1024];
    char* TheName = new char[100];
    char* branchname = new char[100];
    bool choice; // 1 for init, 0 for old directory
    int directChocie = -1;
    bool brokenAngel = false;
    int in = 0;
    char* root = new char[256];
    int gh = 0;

    while (1)
    {
        cout << "\n--------------------------------------------------------------------------------------------------------------------\n";
        cout << "Press '1' >Init " << endl;
        cout << "Press '2' To Open An Existing Directory " << endl;
        cout << "Press '3' To Exit GitLite" << endl;
        cout << "Enter : ";
        cin >> directChocie;

        switch (directChocie)
        {

        case 1:
        {
            cout << "Enter Your Branch Name : ";
            cin >> branchname;
            cout << endl;
            if (fs::exists(branchname))
            {
                cout << "Branch '" << branchname << "' already Exists." << endl;
                continue;
            }

            copyData(currentDir, branchname);
            choice = true;

            if (fs::create_directory(fs::path(branchname)))
            {
                cout << "Branch '" << branchname << "' created successfully." << endl;
                cout << "\n--------------------------------------------------------------------------------------------------------------------\n\n";
                copyData(folderNames[folderCount], currentDir);
                folderCount++;
            }
            brokenAngel = true;
            break;
        }

        case 2:
        {

            cout << "Enter branch name: ";
            cin >> branchname;
            if (fs::exists(branchname))
            {
                cout << "Branch '" << branchname << "' opened successfully." << endl;
                copyData(currentDir, branchname);
            }
            else
            {
                cout << "This branch doesn't exist!\n";
                continue;
            }
            choice = false;
            brokenAngel = true;
            break;
        }

        case 3:
        {
            cout << "\n\n                                         THANKYOU FOR USING GITLITE !\n";
            return 0;
        }

        default:
        {
            cout << "Incorrect Choice" << endl;
            cin.clear();
            cin.ignore();
            brokenAngel = false;
            break;
        }
        }
        if (brokenAngel)
            break;
    }

    if (choice)
    {
        copyData(firstLine, generateTree(branchname, treeChoice, obj1, obj2, obj3));
        char* orgmer = new char[256];
        char* newmer = new char[256];
        int i = 0;
        while (currentDir[i] != '\0') {
            orgmer[i] = currentDir[i];
            newmer[i] = currentDir[i];
            i++;
        }
        int a = i;
        int b = i;

        orgmer[a++] = '/';
        orgmer[a++] = 'm';
        orgmer[a++] = 'e';
        orgmer[a++] = 'r';
        orgmer[a++] = 'k';
        orgmer[a++] = 'l';
        orgmer[a++] = 'e';
        orgmer[a] = '\0';

        newmer[b++] = '/';
        newmer[b++] = 'n';
        newmer[b++] = 'e';
        newmer[b++] = 'w';
        newmer[b++] = 'm';
        newmer[b++] = 'e';
        newmer[b++] = 'r';
        newmer[b++] = 'k';
        newmer[b++] = 'l';
        newmer[b++] = 'e';
        newmer[b] = '\0';

        int count = 0;
        char* arr = new char[30];
        while (currentDir[count] != '\0')
        {
            arr[count] = currentDir[count];
            count++;
        }
        // Append "/commit.txt" to the path
        arr[count++] = '/';
        arr[count++] = 'r';
        arr[count++] = 'o';
        arr[count++] = 'o';
        arr[count++] = 't';
        arr[count++] = '.';
        arr[count++] = 't';
        arr[count++] = 'x';
        arr[count++] = 't';
        arr[count] = '\0'; // Null-terminate the string

        std::ifstream obj(arr, std::ios::in);

        getLineValue(obj, arr, 1);
        obj.close();

        if (treeChoice == 1)
        {

            obj1->callMerkel(orgmer, newmer, arr);
        }
        if (treeChoice == 3)
        {

            obj3->callMerkel(orgmer, newmer, arr);
        }
    }

    fs::path sourceDir; // Specify the source directory
    fs::path destDir;   // Specify the destination directory
    char* lol = new char[50];
    int th = 0;
    int cc = 0; // is being used in versio saving

    while (1)
    {

        cout << "Choose from the following commands:\n    1. >Init\n    2. >Branch\n    3. >CheckOut\n    4. >Commit\n    5. >Branches\n    6. >Display Commit Log\n    7. >Display Tree\n     8. >Exit\n";
        cin >> in;
        switch (in)
        {
        case 1:
            cout << "Enter Your Branch Name : ";
            cin >> branchname;
            cout << endl;

            if (fs::exists(branchname))
            {
                cout << "Branch '" << branchname << "' already Exists." << endl;
                continue;
            }

            copyData(currentDir, branchname);

            if (fs::create_directory(fs::path(branchname)))
            {
                cout << "Branch '" << branchname << "' created successfully." << endl;
            }

            copyData(firstLine, generateTree(branchname, treeChoice, obj1, obj2, obj3));
            copyData(folderNames[folderCount], currentDir);
            folderCount++;
            break;
        case 2:
            cout << "Enter Your Branch Name : ";
            cin >> branchname;
            cout << endl;
            choice = true;

            if (fs::exists(branchname))
            {
                cout << "Branch '" << branchname << "' already exists." << endl;
                break;
            }

            sourceDir = currentDir; // Specify the source directory
            destDir = branchname;   // Specify the destination directory

            if (fs::create_directory(destDir))
            {
                cout << "Branch '" << branchname << "' created Successfully!" << endl;
            }
            else
            {
                std::cout << "Failed to create destination directory.\n";
                break;
            }

            // Copy directory recursively
            fs::copy(sourceDir, destDir, fs::copy_options::recursive);

            std::cout << "Directory copied successfully from '" << sourceDir << "' to '" << destDir << "'.\n";
            break;

        case 3:
            cout << "Enter the Branch Name you want to switch in: ";
            cin >> branchname;
            cout << endl;
            if (!fs::exists(branchname))
            {
                cout << "Branch '" << branchname << "' does not exist." << endl;
            }
            else
            {
                copyData(currentDir, branchname);
                cout << "\nSuccessfully switched to branch '" << currentDir << '\'' << endl;
            }
            break;

        case 4:
            cc++;
            commit(currentDir, firstLine, cc, obj1);
            break;
        case 5:
            cout << "\n----------------------------------------------------------------------------------------------------------\n";
            cout << "Record of the folders:\n";
            for (int i = 0; i < folderCount; i++)
            {
                cout << "Folder " << i + 1 << " : " << folderNames[i] << endl;
            }
            cout << "\n----------------------------------------------------------------------------------------------------------\n";
            break;
        case 6:

            cout << "\n----------------------------------------------------------------------------------------------------------\n";
            cout << "The commit history:\n";
            commitHistory(currentDir);
            system("pause");

            break;
        case 7:
            cout << "Choose the traversal: \n1. Inorder\n2. Preorder\n3. Postorder\n";
            cin >> gh;
            //cout << "\nroot: " << root << endl;
            switch (gh)
            {
            case 1:
                if (treeChoice == 1)
                {
                    obj1->callInorder(obj1->getRoot());
                }
                else if (treeChoice == 3)
                {
                    obj3->callInorder(obj3->getRoot());
                }
                else if (treeChoice == 2)
                {
                    cout << "\nSorry:/        This service is currently unavailable\n";
                }
                break;
            case 2:
                if (treeChoice == 1)
                {
                    obj1->callPreorder(obj1->getRoot());
                }
                else if (treeChoice == 3)
                {
                    obj3->callPreorder(obj3->getRoot());
                }
                else if (treeChoice == 2)
                {
                    cout << "\nSorry:/        This service is currently unavailable\n";
                }
                break;
            case 3:
                if (treeChoice == 1)
                {
                    obj1->callPostorder(obj1->getRoot());
                }
                else if (treeChoice == 3)
                {
                    obj3->callPostorder(obj3->getRoot());
                }
                else if (treeChoice == 2)
                {
                    cout << "\nSorry:/        This service is currently unavailable\n";
                }
                break;
            default:
                break;
            }

            break;
        case 8:
            cout << "\n\n                                       THANKYOU FOR USING GITLITE !\n";
            return 0;
            break;
        default:
            cout << "\nPlease enter correct choice!\n";
            break;
        }
    }
    delete[] currentDir;
    delete[] TheName;
    delete[] firstLine;
    delete[] branchname;
    delete[] lol;

    for (int i = 0; i < 10; i++)
    {
        delete[] folderNames[i];
    }
    delete[] folderNames;
}
