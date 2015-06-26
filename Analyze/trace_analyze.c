#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#define number_type unsigned long long

#include<iostream>
using namespace std;
#include<queue>
#include<list>
class trace_item { 
private:
	unsigned long long time;
	unsigned long long r_w;
	unsigned long long addr;
	unsigned long long dif;
	bool flag_is_OS;
public:
	trace_item (unsigned long long time, unsigned long long r_w, unsigned long long addr, unsigned long long dif, bool is_OS) {
		this->time = time;
		this->r_w = r_w;
		this->addr = addr;
		this->dif = dif;
		this->flag_is_OS = is_OS;
	}
	bool is_OS() {
		return flag_is_OS;
	}

	void set_flag(bool new_flag) {
		flag_is_OS = new_flag;	
	}
	
	void cout_item () {
		if (is_OS())
			printf("OS global_counter %llu r(1)_w(0) %llu address %llx trace_dif %llu\n", time, r_w, addr<<3, dif);	
		else
			printf("global_counter %llu r(1)_w(0) %llu address %llx trace_dif %llu\n", time, r_w, addr<<3, dif);	
	}
};

class List {
private:
	list<trace_item> traces;
	int capacity;
public:
	List () : capacity(3){}

	int size() {
		return traces.size();
	}

	void Insert(trace_item a){
		traces.push_front(a);	
		if(a.is_OS())
			setAsOS();
		if (isFull()){
			popAndDisplay();
		}
	}	

	bool isFull() {
		if (this->size() == this->capacity) {
			return true;
		}
		else 
			return false;
	}

	void setAsOS() {
		for(list<trace_item>::iterator i = traces.begin(); i != traces.end(); i++) {
			i->set_flag(true);	
		}	
	}

	void popAndDisplay() {
		trace_item a = traces.back();	
		a.cout_item();
		traces.pop_back();
	}
};

List my_list;

#define number_type unsigned long long 
unsigned long long total_counter = 0;
typedef struct Field
{
	number_type begin;
	number_type end;
} Field;

struct Field Type;
struct Field Seq_no;
struct Field Trace_dif;
struct Field Trace_r_w;
struct Field Trace_addr;
struct Field Global_counter_seq;
struct Field Global_counter;

number_type type;
number_type seq_no;
number_type trace_dif;
number_type trace_r_w;
number_type trace_addr;
number_type global_counter_seq;
number_type global_counter;

number_type global_time = 0, global_time_prior = 0;

number_type assign_Field(Field *p, number_type begin, number_type end)
{
	p->begin = begin;
	p->end	 = end;
	return 0;
}

number_type ini_Fields()
{
	assign_Field(&Type, 63, 62 ); 
	assign_Field(&Seq_no, 61, 52); 
	assign_Field(&Trace_dif, 51, 32);
	assign_Field(&Trace_r_w, 31, 31);
	assign_Field(&Trace_addr, 30, 0); 
	assign_Field(&Global_counter_seq, 51, 45 ); 
	assign_Field(&Global_counter, 44, 0); 
}

number_type get_field(number_type *p, Field f)
{
	number_type right_shift = f.end;
	number_type mask	= (1ULL<<(f.begin - f.end + 1)) - 1;
	return (number_type)(((*p)>>right_shift) & mask);
}


//number_type type;
//number_type seq_no;
//number_type trace_dif;
//number_type trace_addr;
//number_type global_counter_seq;
//number_type global_counter;

number_type trace_decode(number_type *p)
{
	type = get_field(p, Type);
	seq_no = get_field(p, Seq_no);
	if (type == 0)
	{
		trace_dif = get_field(p, Trace_dif);
		trace_r_w = get_field(p, Trace_r_w);
		trace_addr = get_field(p, Trace_addr);
	}
	else if ((type == 1) || (type == 2))
	{
		global_counter_seq = get_field(p, Global_counter_seq);
		global_counter	= get_field(p, Global_counter);
	}
	else 
	{
		printf("Error, the type value of this trace is wrong!\n");
	}
}

number_type my_printf_global_time(number_type *p)
{	
//	printf("%llx\n", *p);
	static int filter_counter = 7;
	unsigned long long trace_dif_tmp = 0;
	if (type == 0)
	{
	//	printf("%llu %llu %llu %llu %llu\n", type, seq_no, trace_dif, trace_r_w, trace_addr);	
		global_time += trace_dif;
		trace_dif_tmp = global_time - global_time_prior;
	//	if(trace_dif_tmp > 200)
//		if((trace_addr < 0x10000000)) {
//			filter_counter = 10;
//		}
//		
//		if((trace_addr < 0x10000000) || (filter_counter > 0)) {
//			printf("OS ");
//			if(filter_counter > 0)
//				filter_counter--;
//		}
//
//		if(!((trace_addr <= 0x18000000) && (trace_addr >= 0x10000000)))
//			printf("*******************");
//		printf("global_counter %llu r(1)_w(0) %llu address %llx trace_dif %llu\n", global_time, trace_r_w, trace_addr<<3, trace_dif_tmp);	
//		//printf("%llu %llu %llu %llu\n", global_time, global_time - global_time_prior, trace_r_w, trace_addr);	
		bool flag;
	 //if((trace_addr < 0x10000000)) {
		if((trace_addr < 0x8000000)) {   // The range of physical memory is 0 - 256MB
			filter_counter = 3;
		}
		
	 //if((trace_addr < 0x10000000) || (filter_counter > 0)) {
		if((trace_addr < 0x8000000) || (filter_counter > 0)) { // The range of physical memory is 0 - 256MB
			flag = true;	
			if(filter_counter > 0)
				filter_counter--;
		}
	//	trace_item (unsigned long long time, unsigned long long r_w, unsigned long long addr, unsigned long long dif, bool is_OS) {
		my_list.Insert(trace_item(global_time,  trace_r_w, trace_addr, global_time - global_time_prior, flag));
		//printf("%llu %llu %llu %llu\n", global_time, global_time - global_time_prior, trace_r_w, trace_addr);	

		global_time_prior = global_time;
	}
	else if ((type == 1) || (type == 2))
	{
	//	printf("%llu %llu %llu %llu\n", type, seq_no, trace_dif, global_counter_seq, global_counter);	
		if (type == 1) 
			global_time += global_counter;
	}
	else 
	{
		printf("Error, the type value of this trace is wrong!\n");
	}
	//getchar();
}

number_type my_printf(number_type *p)
{	
	printf("%llx\n", *p);
	if (type == 0)
	{
		printf("%llu %llu %llu %llu %llu\n", type, seq_no, trace_dif, trace_r_w, trace_addr);	
	}
	else if ((type == 1) || (type == 2))
	{
		printf("%llu %llu %llu %llu\n", type, seq_no, trace_dif, global_counter_seq, global_counter);	
	}
	else 
	{
		printf("Error, the type value of this trace is wrong!\n");
	}
	//getchar();
}

int main(int argc, char **argv)
{
    char filename[256];
    char outputFilename[256];
    FILE *fp;
	
	number_type buf;

	ini_Fields();
    memset(filename, 0, 256);
    memset(outputFilename, 0, 256);
    if(argc < 3)
    {
        printf("./%s filename\n",argv[0]);
        return 0;
    }
    strcpy(filename, argv[1]);
    strcpy(outputFilename, argv[2]);

    if((fp = fopen(filename, "r")) == NULL)
    {
        printf("Open file %s error\n",filename);
        return 0;	
	}
    //trace analyze
	while(!feof(fp))
	{
		total_counter++;	
		fread(&buf, 8*sizeof(char), 1, fp);
	    	trace_decode(&buf);
		my_printf_global_time(&buf);
		if (strcmp(argv[3], "stop_per_trace") == 0)
			getchar();
	}

   	fclose(fp);

    return 1;

}





