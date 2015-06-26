#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
using namespace std;

class buffer {
private:
	vector<string> a;
	int capacity;
public:
	buffer(int capacity) {
		this->capacity = capacity;
	}
	
	void fill_buf (string str) {
		a.push_back(str);
	}

    void erase () {
        a.erase(a.begin());
    }
	
    bool is_dif_1000(string s) {
		if (s.empty())
			return false;
		int pos_last_of = s.find_last_of(' ');
        int trace_dif = atoi(s.substr(pos_last_of).c_str());

        if (trace_dif > 500)
            return true;
        else 
            return false;
	}

	bool is_dif_50(string s) {
		if (s.empty())
			return false;
		int pos_last_of = s.find_last_of(' ');
        int trace_dif = atoi(s.substr(pos_last_of).c_str());

        if (trace_dif < 50)
            return true;
        else 
            return false;
	}
	
    bool is_r(string str){
        if (str.empty()) {
            return false;
        }

        int length = str.length();
        int i = 0, j = 0;
        for (j=length-1; j>=0; j--) {
            if(str.at(j) == ' ')
                i++;
            if (i == 5)
                break;
        }
        if ((str.at(j+1) - '0') == 0) {
            return false;
        }
        else
            return true;

    }
    
    bool not_os() {
        if((a.at(0).substr(0, 2) != "OS") && (a.at(1).substr(0, 2) != "OS") && (a.at(2).substr(0, 2) != "OS"))   
            return true;
        else 
            return false;
    }
    
    bool is_tuple() {
		if (a.size() < 3) {
			cout << "The vector has not been filled!" << endl;
		}
	    bool b1 = is_r(a.at(0));
		bool b2 = is_dif_1000(a.at(0));
		bool b3 = is_r(a.at(1));
		bool b4 = is_dif_50(a.at(1));
		bool b5 = is_r(a.at(2));
		bool b6 = is_dif_1000(a.at(2));
		bool b7 = not_os();

        if (((!b1) && b2) && (b3 && b4) && ((!b5) && b6) && b7) {
           cout << a.at(1) << " " << a.at(2) << endl; 
           return true;
		}
        else 
            return false;
	}
};

int main(int argc, char *argv[]) {
	buffer buf(3);
	std::fstream fs;
	fs.open (argv[1], std::fstream::in);
	string str;
	
	int i = 0;
	while (i<2) {
		std::getline (fs, str);
		buf.fill_buf(str);
		i++;
	}

	//fillBuf(fs);	
	while (std::getline (fs, str)) {
		buf.fill_buf (str);	
	    buf.is_tuple();	
		buf.erase();
	}
	cout << str;
	fs.close();
	return 1;
  }
	
