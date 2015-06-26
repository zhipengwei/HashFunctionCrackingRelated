#include<iostream>
#include<set>
#include<map>
#include<string>
#include<vector>
#include<fstream>
#include<queue>
using namespace std;

class Classifier 
{
    private:
        multimap<unsigned long long, unsigned long long> graph;
        vector< vector<unsigned long long> > result;
        std::ifstream ifs;
    public:
        void init_graph(char* dir)
        {
            ifs.open(dir, std::fstream::in);
            string str;
            unsigned long long sp, tp;
            while(getline(ifs, str))
            {
                //cout << "String is " << str << endl;
                std::size_t i = str.find_first_of(' '); 
                //cout << i << endl;
                string substr = str.substr(0, i);
                //cout << "substr 1 is " << substr << endl;
                sp = stoi(substr, 16);
                substr = str.substr(i+1, str.length() - i);
                //cout << "substr 2 is " << substr << endl;
                tp = stoi(substr, 16);
                //cout << sp << ' ' << tp << endl;
                //printf("%llx %llx\n", sp, tp);
                
                graph.insert(std::pair<unsigned long long, unsigned long long>(sp, tp));
                graph.insert(std::pair<unsigned long long, unsigned long long>(tp, sp));
            }
        }

        unsigned long long stoi(string str, int base)
        {
            unsigned long long result = 0, value = 0;
            if(base == 10){
                for(std::string::iterator i = str.begin(); i != str.end(); i++)
                {
                    value = *i - '0';
                    result = result * 10 + value;
                }
            }
            if(base == 16)
            {
                for(std::string::iterator i = str.begin(); i != str.end(); i++)
                {
                    if ((*i <= 'f') && (*i >= 'a'))
                        value = *i - 'a' + 10;
                    else 
                        value = *i - '0';
                    result = result * 16 + value;
                }
            }
            return result;
        }

        void display_graph()
        {
            for(std::map<unsigned long long, unsigned long long>::iterator i = graph.begin(); i != graph.end(); i++)
            
            {
                cout << i->first << " " << i->second << endl;
            }
            
        }

        void classify()
        {
            queue<unsigned long long> q;
            vector<unsigned long long> tmp_result;
            while(!graph.empty())
            {
                unsigned long long cur = graph.begin()->first;
                map<unsigned long long, unsigned long long>::iterator it;
                q.push(cur);

                while(!q.empty()) 
                {
                    cur = q.front(); 
                    q.pop();
                    tmp_result.push_back(cur);
                    while((it = graph.find(cur)) != graph.end())
                    {
                        q.push(it->second);
                        graph.erase(it);
                    }
                }
                set<unsigned long long> s(tmp_result.begin(), tmp_result.end()); 
                tmp_result.assign(s.begin(), s.end());
                result.push_back(tmp_result);

                tmp_result.clear();

            }
        }
        void display_result()
        {
            cout << "There are " << result.size() << " classfications in total." << endl;
            for(vector< vector<unsigned long long> >::iterator it=result.begin(); it != result.end(); it++)
            {
                cout << it->size() << " ";
            }
            cout << endl;
            for(vector< vector<unsigned long long> >::iterator it=result.begin(); it != result.end(); it++)
            {
                for(vector<unsigned long long>::iterator i=it->begin(); i != it->end(); i++)
                    //cout << *i << endl;
                    printf("%llx\n", *i);

                cout << endl;
            }
        }
};

int main(int argc, char *argv[]) 
{
    Classifier my_classfier;
    my_classfier.init_graph(argv[1]);
//    my_classfier.display_graph();
    my_classfier.classify();
    my_classfier.display_result();
    return 1;
      
}

