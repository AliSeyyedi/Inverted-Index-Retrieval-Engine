#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<cctype>
#include<algorithm>
using namespace std;
string  stringtolower(string word)
{
    for (int i = 0; i < word.size(); i++)
    {
        word[i] = tolower(word[i]);
    }
    return word;
}
struct  postinglist     
{
    string  file;
//    int line;
//    int index;
};
class   invertedIndex   
{
    map<string, vector<postinglist> > dictionary;
    vector<string> fileList;
    vector<vector<string>> retrievalResult;

    public:
    void showFiles();
    void addFile(string filename);
    void retrieval(string word);
    void finalResult();
};
void    invertedIndex::showFiles()
{
    int size = fileList.size();
    for (int i = 0; i < size; i++)
        cout << i+1  << ": " << fileList[i] << endl;

    if (!size) cout << "No files found\n";
}
void    invertedIndex::addFile(string filename)
{
    ifstream fp;
    fp.open(filename, ios::in);

    if (!fp)
    {
        cout << "File Not Found!\n";
        return;
    }
    
    for (int i = 0; i < fileList.size(); i++)
        if (fileList[i]==filename)
        {
            cout << "File Added\n";
            return;
        }

    cout << "File Added\n";
    fileList.push_back(filename);
    string line, word;
//    int line_number = 0, word_number = 0;

    while (getline(fp, line))
    {
//        line_number++;
//        word_number = 0;
        stringstream s(line);
        while (s >> word)
        {
            word = stringtolower(word);
            postinglist obj;
            obj.file = filename;
//            obj.line = line_number;
//            obj.index = word_number;
            dictionary[word].push_back(obj);
        }
    }

    fp.close();
}
void    invertedIndex::retrieval(string word)
{
    vector <string> wordFiles;

    if (dictionary.find(word) == dictionary.end())
    {
        cout << "No instance exist\n";
        return;
    }

    for (int i = 0; i < dictionary[word].size(); i++) 
            wordFiles.push_back(dictionary[word][i].file);
    
    cout << dictionary[word].size() << " Times: "<<word<< "\t->" <<" File Name:\t";

    sort(wordFiles.begin(), wordFiles.end());
    wordFiles.erase(unique(wordFiles.begin(), wordFiles.end()), wordFiles.end());

    for (int i = 0; i < wordFiles.size(); i++)
        cout<<wordFiles[i]<<"\t";
    cout << endl ;

    retrievalResult.push_back(wordFiles);
//    for (int i = 0; i < size; i++) {
//        cout << i + 1 << ": \n";
//        cout <<word<< "\t->" <<"\tFile Name:"<< dictionary[word][i].file  << endl;
//        cout << "   Line Number: " << dictionary[word][i].line  << endl;
//        cout <<       "   Index: " << dictionary[word][i].index << endl;
//    }
}
void    invertedIndex::finalResult()
{
    vector <string> searchResult;
    vector <string> t;
    int i=0, j = 0, k = 0;
    if (retrievalResult.size()==0)
    {
        return;
    }

    for (int i = 0; i < retrievalResult[0].size(); i++)
    {
            t.push_back(retrievalResult[0][i]);
    }

    for (k = 1; k < retrievalResult.size(); k++)
    {
        for (i = 0; i < t.size(); i++)
        {
            for (j = 0; j < retrievalResult[k].size(); j++)
            {
                if (t[i] == retrievalResult[k][j])
                {
                    searchResult.push_back(t[i]);
                }
            }
        }
        if (searchResult.size() == 0)
        {
            cout << "Nothing found !!!" << endl <<endl;
            return;
        }
        t.clear();
        for (int l = 0; l < searchResult.size(); l++)
        {
            t.push_back(searchResult[l]);
        }
        searchResult.clear();
    }

    if (t.size() != 0)
    {
        cout <<"Final Result: ";
        for (int i = 0; i < t.size(); i++)
           cout << t[i] << "\t";
    }

    searchResult.clear();
    retrievalResult.clear();
    cout << endl<<endl;
}

int main(int argc, char* argv[])
{    
    invertedIndex Data;

    for (int i = 1; i < argc; i++)
    {
        Data.addFile(argv[i]);
    }
 
    do
    {
        int choice = 0;
        cout << "1: Show Files\n2: Add File\n3: Inverted Index Retrieval\n4: Exit\n";
        cin >> choice;    
        system("CLS");
        cin.clear();
        cin.ignore();
        switch (choice)
        {
            case 1:
            {
                Data.showFiles();
                break;
            }
            case 2:
            {
                cout << "Enter File Name: ";
                string name;
                cin >> name;
                Data.addFile(name);
                break;
            }
            case 3:
            {
                cout << "To Rerieve More Than 1 Word Use & As Separator And Operator For Example: Antony&Brutus\n";
                cout << "Enter Word/s: ";
                string word;
                cin >> word;
                word = stringtolower(word);
                vector <string> words;
                string delimiter = "&";

                int position = 0;
                while ((position = word.find(delimiter)) != string::npos)
                {
                    string token = word.substr(0, position);
                    words.push_back(token);
                    word.erase(0, position + delimiter.length());
                }
                words.push_back(word);

                cout << endl;
                for (int i = 0; i < words.size(); i++)
                    Data.retrieval(words[i]);
                cout << endl;
                if (words.size() > 1)
                    Data.finalResult();
                break;
            }
            case 4:
            {
                return 0;
                break;
            }
            default:
            {
                cout << "Try Again!\n";
                break;
            }                
        }
    } while (1);
}
