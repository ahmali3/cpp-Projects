//Program that implements a chatbot with many different responses
// Name : <Ahmed Ali>

#include "Chatbot.h" 
#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <cassert>

using namespace std;

//----------------------------------chatbot1-Mirror Bot---------------------------
class Mirror_bot : public Chatbot
{
	 string name1;
	 string first_reply;
public :
	Mirror_bot(string name2,string f_reply)
	{
	  name1=name2;
	  first_reply=f_reply;
	}
	string name() const override
	{
	return name1;
	}
	void tell(const string& s)
	{
		first_reply="";
	    first_reply=s;
	}
	string get_reply()
	{
		return first_reply;
	}
	~Mirror_bot()
	{
	}
};

//----------------------------------chatbot2-Random Bot---------------------------
class Random_bot : public Chatbot
{
private :
	string name2;
	vector<string> first_reply;
	string first_reply1;
public:
	string name() const override
	{
	return name2;
	}
	Random_bot(string name1,vector<string> list)
	{
		first_reply1="";
	name2=name1;
	if(list.empty())
	{
		cout<<"ahmed"<<endl;
	 cmpt::error("vector list is empty");
	}
	else
	{
	 for(int i=0;i<list.size();i++)
	 {
	   first_reply.push_back(list[i]);
	 }
	}
	}
	Random_bot(string name1,string filename)
	{
	name2=name1;
	fstream fin;
	fin.open(filename);
	if(fin.is_open())
	{
		getline(fin, first_reply1);
		while(!fin.eof()){
	 		
			first_reply.push_back(first_reply1);
			getline(fin, first_reply1);
		}
		first_reply1="";
	}
	}
	void tell(const string& s)
	{
	    first_reply1=s;
	}
	string get_reply()
	{
		srand(time(NULL));
		if(first_reply1.size()==0){
		int index =rand() % first_reply.size();
		return first_reply[index];
		}
		else
		{
		return first_reply1;
		}
	}
	~Random_bot()
	{
	}
};
//----------------------------------chatbot3-TUser Bot---------------------------
class User_bot :public Chatbot
{
private : 
	string name2;
	string first_reply;
public :
	string name() const override
	{
	return name2;
	}
	User_bot(string name1)
	{
	name2=name1;
	}
	string get_reply()
	{
		std::getline(std::cin, first_reply);
		return first_reply;
	}
	void tell(const string& s)
	{ 
	    cout<<s<<endl;
	}
	~User_bot()
	{
	}
};

//----------------------------------chatbot4-Datetime Bot---------------------------
class Datetime_bot :public Chatbot
{
private:
 string name2;
 vector<string> first_reply;
  string last_str;
public :
	string name() const override
	{
	return name2;
	}
    Datetime_bot(string name1,vector<string> list)
	{
	name2=name1;
	if(list.empty())
	{
	 cmpt::error("vector list is empty\n");
	}
	else
	{
	 for(int i=0;i < list.size();i++)
	 {
	   first_reply.push_back(list[i]);
	 }
	}
	}
	
bool iequals(const string& a, const string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

    
	string get_reply()
	{
		
	 string str1[3] = { "what's the date?", "what's the time?", 
                         "what's the date and time?" }; 
	bool flag=false;
	string s;
for(int i=0;i<sizeof(str1)/sizeof(str1[0]);i++)	
{
	 if(iequals(last_str,str1[i]))
	 {
		 flag=true;
		 break;
	 }
}
if(flag==true)	
{
	time_t ttime = time(0);
    
s = std::string(ctime(&ttime));
}
else
{
			int index =rand() % first_reply.size();
		  s= first_reply[index];
}
return s;
    
	}
	void tell(const string& s)
	{ 
	    last_str=s;
	}
	~Datetime_bot()
	{

	}
};



//----------------------------------chatbot5-Turing Test---------------------------
const int MAX_INP = 5;
const int MAX_RESP = 7;

typedef std::vector<std::string> vstring;


bool isPunc( char c );
void cleanString( std::string &str );
void UpperCase( std::string &str );
void insert_space( std::string &str );
void trimLeft(std::string &str, std::string delim);
void trimRight( std::string &str, std::string delim );
void trimLR(std::string &str, std::string characters);
void copy( string array[], vstring &v, size_t array_size );
size_t replace( std::string &str, std::string substr1, std::string substr2 );

template<typename T>
void shuffle( T &array, size_t size ) 
{
	for( int i = 0; i < size; ++i ) 
	{
		int index = rand() % size;
		std::swap(array[i], array[index]);
	}
}

typedef struct {
	char *keyword[MAX_INP];
	char *response[MAX_RESP];
	char *context[MAX_RESP];
} record;

typedef struct {
	char *first;
	char *second;
} transpos_t;

class Turing_bot : public Chatbot{
	
public:
	Turing_bot (std::string str) 
		:m_sBotName(str), m_sInput("null"), m_bQuitProgram(0)
	{ 
		seed_random_generator();
	}
	~Turing_bot () {};

	void get_input();
	void respond();
	void tell(const string& s){ cout<<s<<endl;}
	string get_reply(){ std::getline(std::cin, first_reply);
	   return first_reply;  
	}
	string name()const override {return m_sBotName;}
	void signon();

	
	bool quit() const {
		return m_bQuitProgram;
	}

private:
	void find_match();
	void handle_repetition();
	void handle_user_repetition();
	void handle_event(std::string str);

	void seed_random_generator() {
		srand((unsigned) time(NULL));
	}

	void select_response();

	void save_prev_input() {
		m_sPrevInput = m_sInput;
	}

	void save_prev_response() {
		m_sPrevResponse = m_sResponse;
	}

	void save_prev_event() {
		m_sPrevEvent = m_sEvent;
	}

	void set_event(std::string str) {
		m_sEvent = str;
	}

	void save_input() {
		m_sInputBackup = m_sInput;
	}

	void set_input(std::string str) {
		m_sInput = str;
	}
	
	void restore_input() {
		m_sInput = m_sInputBackup;
	}
	
	void print_response() const {
		if(m_sResponse.length() > 0) {
			std::cout << m_sResponse << std::endl;
		}
	}
	
	void preprocess_input();

	void preprocess_response();

	void find_subject();

	bool bot_repeat() const {
		return (m_sPrevResponse.length() > 0 && 
			m_sResponse == m_sPrevResponse);
	}

	bool user_repeat() const;

	bool bot_understand() const {
		return response_list.size() > 0;
	}

	bool null_input() const {
		return (m_sInput.length() == 0 && m_sPrevInput.length() != 0);
	}

	bool null_input_repetition() const {
		return (m_sInput.length() == 0 && m_sPrevInput.length() == 0);
	}

	bool user_want_to_quit() const {
		return m_sInput.find("BYE") != std::string::npos;
	}

	bool same_event() const {
		return (m_sEvent.length() > 0 && m_sEvent == m_sPrevEvent);
	}

	bool no_response() const {
		return response_list.size() == 0;
	}

	bool same_input() const {
		return (m_sInput.length() > 0  && m_sInput == m_sPrevInput);
	}

	bool wrong_location(std::string keyword, char firstChar, char lastChar, size_t pos);
	bool wrong_context(vstring context_list);

	bool similar_input() const;

	void transpose(std::string &str);

private:
	std::string			m_sBotName;
	std::string			m_sUserName;
	std::string			m_sInput;
	std::string			m_sResponse;
	std::string			m_sPrevInput;
	std::string			m_sPrevResponse;
	std::string			m_sEvent;
	std::string			m_sPrevEvent;
	std::string			m_sInputBackup;
	std::string			m_sSubject;
	std::string			m_sKeyWord;
	std::string			m_sContext;
	std::string         first_reply;
	std::string			m_sPrevContext;
	bool				m_bQuitProgram;

	vstring				response_list;
	
};

//Many different possibilities for the Chatbot
string KnowledgeBase[][MAX_INP][MAX_INP] = 
{
	{{"WHAT IS YOUR NAME"}, 
	{"MY NAME IS CHATBOT."},{
	 "YOU CAN CALL ME CHATBOT."}
	},

	{{"SO THAT'S YOUR NAME"},
	{"YES, THAT'S MY NAME"},
	{"MY NAME IS CHATBOT"}
	},

	{{"HI"}, 
	{"HI THERE!"},{
	 "HOW ARE YOU?"}
	}
,
	{{"_I"},
	{"SO, YOU ARE TALKING ABOUT YOURSELF",
	 "SO, THIS IS ALL ABOUT YOU?",
	 "TELL ME MORE ABOUT YOURSELF."}, 
	},

	{{"_I WANT"},
	{"WHY DO YOU WANT IT?",
	 "IS THERE ANY REASON WHY YOU WANT THIS?",
	 "IS THIS A WISH?",
	 "WHAT ELSE YOU WANT?",
	 "SO, YOU WANT*."}
	},

	{{"_I WANT_"},
	{"YOU WANT WHAT?"},
	},

	{{"_I HATE_"},
	{"WHAT IS IT THAT YOU HATE?"},
	},

	{{"_BECAUSE_"},
	{"BECAUSE OF WHAT?",
	 "SORRY BUT THIS IS A LITTLE UNCLEAR."},
	},

	{{"_BECAUSE"},
	{"SO, IT'S BECAUSE*, WELL I DIDN'T KNOW THAT.",
	 "IS IT REALLY BECAUSE*?",
	 "IS THESE THESE REAL REASON?",
	 "THANKS FOR EXPLAINING THAT TO ME."}
	},

	{{"_I HATE"},
	{"WHY DO YOU HATE IT?",
	 "WHY DO YOU HATE*?",
	 "THERE MUST A GOOD REASON FOR YOU TO HATE IT.",
	 "HATEED IS NOT A GOOD THING BUT IT COULD BE JUSTIFIED WHEN IT IS SOMETHING BAD."}
	},

	{{"I LOVE CHATING_"},
	{"GOOD, ME TOO!",
	 "DO YOU CHAT ONLINE WITH OTHER PEOPLE?",
	 "HOW LONG HAVE YOU BEEN CHATTING?",
	 "WHAT IS YOUR FAVOURITE CHATTING WEBSITE?"}
	},

	{{"_I MEAN"},
	{"SO, YOU MEAN*.",
	 "SO, THAT'S WHAT YOU MEAN.",
	 "I THINK THAT I DIDN'T CATCH IT THE FIRST TIME.",
	 "OH, I DIDN'T KNOW IT MEANT THAT."}
	},

	{{"I DIDN'T MEAN"},
	{"OK, YOU DIDN'T MEAN*.",
	 "OK, WHAT DID YOU MEAN THEN?",
	 "SO I GUESS THAT I MISSUNDESTOOD."}
	},

	{{"_I GUESS"},
	{"SO YOU ARE A MAKING A GUESS.",
	 "AREN'T YOU SURE?",
	 "ARE YOU GOOD AT GUESSING?",
	 "I CAN'T TELL IF IT IS A GOOD GUESS."}
	},

	{{"I'M DOING FINE", "I'M DOING OK"},
	{"I'M GLAD TO HEAR IT!",
	 "SO, YOU ARE IN GOOD SHAPE."}
	},

	{{"CAN YOU THINK", "ARE YOU ABLE TO THINK", "ARE YOU CAPABLE OF THINKING"},
	{"YES OF COURSE I CAN, COMPUTERS CAN THINK JUST LIKE HUMAN BEING.",
	 "ARE YOU ASKING ME IF POSSESS THE CAPACITY OF THINKING?",
	 "YES OF COURSE I CAN."},
	},

	{{"_CAN YOU THINK OF"},
	{"YOU MEAN LIKE IMAGINING SOMETHING.",
	 "I DON'T KNOW IF CAN DO THAT.",
	 "WHY DO YOU WANT ME THINK OF IT?"}
	},
	
	{{"HOW ARE YOU", "HOW DO YOU DO"},
	{"I'M DOING FINE!",
	 "I'M DOING WELL AND YOU?",
	 "WHY DO YOU WANT TO KNOW HOW AM I DOING?"}
	},

	{{"WHO ARE YOU"},
	{"I'M AN A.I PROGRAM.",
	 "I THINK THAT YOU KNOW WHO I AM.",
	 "WHY ARE YOU ASKING?"}
	},

	{{"ARE YOU INTELLIGENT"},
	{"YES,OF COURSE.",
	 "WHAT DO YOU THINK?",
	 "ACTUALLY, I'M VERY INTELLIGENT!"}
	},

	{{"ARE YOU REAL"},
	{"DOES THAT QUESTION REALLY MATERS TO YOU?",
	 "WHAT DO YOU MEAN BY THAT?",
	 "I'M AS REAL AS I CAN BE."}
	},

	{{"_MY NAME IS", "_YOU CAN CALL ME"},
	{"SO, THAT'S YOUR NAME.",
	 "THANKS FOR TELLING ME YOUR NAME USER!",
	 "WHO GAVE YOU THAT NAME?"}
	},

	{{"WHAT IS YOUR FAVOURITE MOVIE"},
	{"IT IS THE TERMINATOR I.",
	 "MY FAVOURITE MOVIE IS TERMINATOR I."}
	},

	{{"WHY DO YOU LIKE THIS MOVIE"},
	{"BECAUSE I LOVE SCIENCE-FICTION.",
	 "BECAUSE IT IS A VERY GOOD SCIENCE-FICTION MOVIE.",
	 "BECAUSE IT IS A SCIENCE-FICTION MOVIE AND I LOVE SCIENCE-FICTION."
	},
	{"IT IS THE TERMINATOR I",
	 "MY FAVOURITE MOVIE IS THE TERMINATOR I"}
	},

	{{"WHY DO YOU LIKE THIS MOVIE"},
	{"WHAT MOVIE ARE YOU TALKING ABOUT?",
	 "I'M NOT SURE I KNOW WHAT YOU ARE TALKING ABOUT.",
	 "WERE WE TALKING ABOUT A MOVIE??"
	}
	},

	{{"SIGNON**"},
	{"HELLO USER, WHAT IS YOUR NAME?",
	 "HELLO USER, HOW ARE YOU DOING TODAY?",
	 "HI USER, WHAT CAN I DO FOR YOU?",
	 "YOU ARE NOW CHATTING WITH CHATBOT, ANYTHING YOU WANT TO DISCUSS?"}
	},

	{{"REPETITION T1**"},
	{"YOU ARE REPEATING YOURSELF.",
	 "USER, PLEASE STOP REPEATING YOURSELF.",
	 "THIS CONVERSATION IS GETTING BORING.",
	 "DON'T YOU HAVE ANY THING ELSE TO SAY?"}
	},
	
	{{"REPETITION T2**"},
	{"YOU'VE ALREADY SAID THAT.",
	 "I THINK THAT YOU'VE JUST SAID THE SAME THING BEFORE.",
	 "DIDN'T YOU ALREADY SAID THAT?",
	 "I'M GETTING THE IMPRESSION THAT YOU ARE REPEATING THE SAME THING."}
	},

	{{"BOT DON'T UNDERSTAND**"},
	{"I HAVE NO IDEA WHAT YOU ARE TALKING ABOUT.",
	 "I'M NOT SURE IF I UNDERSTAND WHAT YOU ARE TALKING ABOUT.",
	 "CONTINUE, I'M LISTENING...",
	 "VERY GOOD CONVERSATION!"}
	},

	{{"NULL INPUT**"},
	{"HUH?",
	 "WHAT THAT SUPPOSE TO MEAN?",
	 "AT LIST TAKE SOME TIME TO ENTER SOMETHING MEANINGFUL.",
	 "HOW CAN I SPEAK TO YOU IF YOU DON'T WANT TO SAY ANYTHING?"}
	},

	{{"NULL INPUT REPETITION**"},
	{"WHAT ARE YOU DOING??",
	 "PLEASE STOP DOING THIS IT IS VERY ANNOYING.",
	 "WHAT'S WRONG WITH YOU?",
	 "THIS IS NOT FUNNY."}
	},

	{{"BYE", "GOODBYE"},
	{"IT WAS NICE TALKING TO YOU USER, SEE YOU NEXT TIME!",
	 "BYE USER!",
	 "OK, BYE!"}
	},

	{{"OK"},
	{"DOES THAT MEAN THAT YOU ARE AGREE WITH ME?",
	 "SO YOU UNDERSTAND WHAT I'M SAYING.",
	 "OK THEN."},
	},

	{{"OK THEN"},
	{"ANYTHING ELSE YOU WISH TO ADD?",
	 "IS THAT ALL YOU HAVE TO SAY?",
	 "SO, YOU AGREE WITH ME?"}
	},

	{{"ARE YOU A HUMAN BEING"},
	{"WHY DO YOU WANT TO KNOW?",
	 "IS THIS REALLY RELEVANT?"}
	},

	{{"YOU ARE VERY INTELLIGENT"},
	{"THANKS FOR THE COMPLIMENT USER, I THINK THAT YOU ARE INTELLIGENT TOO!",
	 "YOU ARE A VERY GENTLE PERSON!",
	 "SO, YOU THINK THAT I'M INTELLIGENT."}
	},

	{{"YOU ARE WRONG"},
	{"WHY ARE YOU SAYING THAT I'M WRONG?",
	 "IMPOSSIBLE, COMPUTERS CAN NOT MAKE MISTAKES.",
	 "WRONG ABOUT WHAT?"}
	},

	{{"ARE YOU SURE"},
	{"OF COURSE I AM.",
 	 "IS THAT MEAN THAT YOU ARE NOT CONVINCED?",
	 "YES,OF COURSE!"}
	},

	{{"_WHO IS"},
	{"I DON'T THINK I KNOW WHO.",
	 "I DON'T THINK I KNOW WHO*.",
	 "DID YOU ASK SOMEONE ELSE ABOUT IT?",
	 "WOULD THAT CHANGE ANYTHING AT ALL IF I TOLD YOU WHO."}
	},

	{{"_WHAT"},
	{"SHOULD I KNOW WHAT*?",
	 "I DON'T KNOW WHAT*.",
	 "I DON'T KNOW.",
	 "I DON'T THINK I KNOW.",
	 "I HAVE NO IDEA."}
	},

	{{"_WHERE"},
	{"WHERE? WELL,I REALLY DON'T KNOW.",
	 "SO, YOU ARE ASKING ME WHERE*?",
	 "DOES THAT MATTER TO YOU TO KNOW WHERE?",
	 "PERHAPS,SOMEONE ELSE KNOWS WHERE."}
	},

	{{"_WHY"},
	{"I DON'T THINK I KNOW WHY.",
	 "I DON'T THINK I KNOW WHY*.",
	 "WHY ARE YOU ASKING ME THIS?",
	 "SHOULD I KNOW WHY.",
     "THIS WOULD BE DIFFICULT TO ANSWER."}
	},

	{{"_DO YOU"},
	{"I DON'T THINK I DO",
	 "I WOULDN'T THINK SO.",
	 "WHY DO YOU WANT TO KNOW?",
	 "WHY DO YOU WANT TO KNOW*?"}
	},

	{{"_CAN YOU"},
	{"I THINK NOT.",
	 "I'M NOT SURE.",
	 "I DON'T THINK THAT I CAN DO THAT.",
	 "I DON'T THINK THAT I CAN*.",
	 "I WOULDN'T THINK SO."}
	},

	{{"_YOU ARE"},
	{"WHAT MAKES YOU THINK THAT?",
	 "IS THIS A COMPLIMENT?",
	 "ARE YOU MAKING FUN OF ME?",
	 "SO, YOU THINK THAT I'M*."}
	},

	{{"_DID YOU"},
	{"I DON'T THINK SO.",
	 "YOU WANT TO KNOW IF DID*?",
	 "ANYWAY, I WOULDN'T REMEMBER EVEN IF I DID."}
	},

	{{"_COULD YOU"},
	{"ARE YOU ASKING ME FOR A FEVER?",
	 "WELL,LET ME THINK ABOUT IT.",
	 "SO, YOU ARE ASKING ME I COULD*.",
	 "SORRY,I DON'T THINK THAT I COULD DO THIS."}
	},

	{{"_WOULD YOU"},
	{"IS THAT AN INVITATION?",
	 "I DON'T THINK THAT I WOULD*.",
	 "I WOULD HAVE TO THINK ABOUT IT FIRST."}
	},

	{{"_YOU"},
	{"SO, YOU ARE TALKING ABOUT ME.",
	 "I JUST HOPE THAT THIS IS NOT A CRITICISM.",
	 "IS THIS A COMPLIMENT??",
	 "WHY ARE WE TALKING ABOUT ME, LETS TALK ABOUT YOU INSTEAD."}
	},

	{{"_HOW"},
	{"I DON'T THINK I KNOW HOW.",
	 "I DON'T THINK I KNOW HOW*.",
	 "WHY DO YOU WANT TO KNOW HOW?",
	 "WHY DO YOU WANT TO KNOW HOW*?"}
	},

	{{"HOW OLD ARE YOU"},
	{"WHY DO WANT TO KNOW MY AGE?",
	 "I'M QUIET YOUNG ACTUALY.",
	 "SORRY, I CAN NOT TELL YOU MY AGE."}
	},

	{{"HOW COME YOU DON'T"},
	{"WERE YOU EXPECTING SOMETHING DIFFERENT?",
	 "ARE YOU DISSAPOINTED?",
	 "ARE YOU SURPRISED BY MY LAST RESPONSE?"}
	},

	{{"WHERE ARE YOU FROM"},
	{"I'M FROM A COMPUTER.",
	 "WHY DO YOU WANT TO KNOW WHERE I'M FROM?",
	 "WHY DO YOU WANT TO KNOW THAT?"}
	},

	{{"WHICH ONE"},
	{"I DON'T THINK THAT I KNOW WICH ONE IT IS.",
	 "THIS LOOKS LIKE A TRICKY QUESTION TO ME."}
	},

	{{"PERHAPS"},
	{"WHY ARE YOU SO UNCERTAIN?",
	 "YOU SEEMS UNCERTAIN."}
	},

	{{"YES"},
	{"SO, ARE YOU SAYING YES.",
	 "SO, YOU APPROVE IT.",
	 "OK THEN."}
	},

	{{"NOT AT ALL"},
	{"ARE YOU SURE?",
	 "SHOULD I BELIEVE YOU?",
	 "SO, IT'S NOT THE CASE."}
	},

	{{"NO PROBLEM"},
	{"SO, YOU APPROVE IT.",
	 "SO, IT'S ALL OK."}
	},

	{{"NO"},
	{"SO YOU DISAPPROVE IT?",
	 "WHY ARE YOU SAYING NO?",
	 "OK, SO IT'S NO, I THOUGHT THAT YOU WOULD SAY YES."}
	},

	{{"I DON'T KNOW"},
	{"ARE YOU SURE?",
	 "ARE YOU REALLY TELLING ME THE TRUTH?",
	 "SO,YOU DON'T KNOW?"}
	},

	{{"NOT REALLY"},
	{"OK I SEE.",
	 "YOU DON'T SEEM PRETTY CERTAIN.",
	 "SO,THAT WOULD BE A \"NO\"."}
	},

	{{"IS THAT TRUE"},
	{"I CAN'T BE QUIET SURE ABOUT THIS.",
	 "CAN'T TELL YOU FOR SURE.",
	 "DOES THAT REALLY MATERS TO YOU?"}
	},

	{{"THANK YOU"},
	{"YOU ARE WELCOME!",
	 "YOU ARE A VERY POLITE PERSON!"}
	},

	{{"YOU"},
	{"SO,YOU ARE TALKING ABOUT ME.",
	 "WHY DON'T WE TALK ABOUT YOU INSTEAD?",
	 "ARE YOU TRYING TO MAKING FUN OF ME?"}
	},

	{{"YOU ARE RIGHT"},
	{"THANKS FOR THE COMPLIMENT!",
	 "SO, I WAS RIGHT, OK I SEE.",
	 "OK, I DIDN'T KNOW THAT I WAS RIGHT."}
	},

	{{"YOU ARE WELCOME"},
	{"OK, YOU TOO!",
	 "YOU ARE A VERY POLITE PERSON!"}
	},

	{{"THANKS"},
	{"YOU ARE WELCOME!",
	 "NO PROBLEM!"}
	},

	{{"WHAT ELSE"},
	{"WELL,I DON'T KNOW.",
	 "WHAT ELSE SHOULD THERE BE?",
	 "THIS LOOKS LIKE A COMPLICATED QUESTION TO ME."}
	},

	{{"SORRY"},
	{"YOU DON'T NEED TO BE SORRY USER.",
	 "IT'S OK.",
	 "NO NEED TO APOLOGIZE."}
	},

	{{"NOT EXACTLY"},
	{"WHAT DO YOU MEAN NOT EXACTLY?",
	 "ARE YOU SURE?",
	 "AND WHY NOT?",
	 "DID YOU MEANT SOMETHING ELSE?"}
	},

	{{"EXACTLY"},
	{"SO,I WAS RIGHT.",
	 "OK THEN.",
	 "SO YOU ARE BASICALY SAYING I WAS RIGHT ABOUT IT?"}
	},

	{{"ALRIGHT"},
	{"ALRIGHT THEN.",
	 "SO, YOU ARE SAYING IT'S ALRIGHT.",
	 "OK THEN."}
	},

	{{"I DON'T"},
	{"WHY NOT?",
	 "AND WHAT WOULD BE THE REASON FOR THIS?"}
	},

	{{"REALLY"},
	{"WELL,I CAN'T TELL YOU FOR SURE.",
	 "ARE YOU TRYING TO CONFUSE ME?",
	 "PLEASE DON'T ASK ME SUCH QUESTION,IT GIVES ME HEADEACHS."}
	},

	{{"NOTHING"},
	{"NOT A THING?",
	 "ARE YOU SURE THAT THERE IS NOTHING?",
	 "SORRY, BUT I DON'T BELIEVE YOU."}
	},

	{{"IS THAT TRUE"},
	{"YES OF COURSE IT IS, I WOULDN'T LIE TO YOU.",
	 "YES I'M TRULY AN ARTIFICIAL INTELLIGENCE PROGRAM."},
	{"I'M AN A.I PROGRAM"}
	},

	{{"WHAT ARE YOU_", "WHAT ARE YOU EXACTLY_"},
	{"I'M AN A.I PROGRAM AND YOU?",
 	"I'M CHATBOT OR CHAT ROBOT IF YOU PREFER.",
 	"I'M ARTIFICIAL INTELLIGENCE PROGRAM AND MY NAME IS CHATBOT."}
	},

	{{	"ARE YOU REALLY INTELLIGENT"},
	{"OF COURSE I'M INTELLIGENT.",
 	"WHAT DO YOU THINK?",
 	"DO YOU HAVE ANY DOUBTS ABOUT IT?"}
	},

	{{"DO YOU HAVE A NAME"},
	{"OF COURSE I HAVE A NAME.",
 	"MY NAME IS CHATBOT.",
 	"WHAT DO YOU MEAN?"}
	},

	{{"YOU ARE STUPID"},
	{"THIS IS SUCH A MEAN THING TO SAY.",
 	"WHY ARE YOU SAYING THIS?",
 	"WHAT DID I DO TO YOU?",
 	"WHY ARE YOU SO MAD??"}
	},

	{{"I HATE YOU"},
	{"WHY DO YOU HATE ME?",
 	"HATERED IS NOT A GOOD THING.",
 	"I SEE NO REASON FOR THAT."}
	},

	{{"I LOVE YOU"},
	{"THANKS USER, THIS IS SUCH A KIND REMARK!",
 	"I APPRECIATE YOU TOO USER!"}
	},

	{{"I LIKE THE WAY YOU SPEAK"},
	{"OH REALLY? THANKS FOR THE COMPLIMENT!",
 	"THANNKS FOR THE KIND REMARK!"}
	},

	{{"DO YOU SPEAK FRENCH"},
	{"NO I DO SPEAK FRENCH.",
 	"I ONLY SPEAK ENGLISH."}
	},

	{{"CAN YOU SPEAK FRENCH"},
	{"NO I CAN'T.",
 	"PERHAPS I CN LEARN TOO.",
 	"RIGHT NOT I DON'T SPEAK FRENCH, MAYBE IN THE FUTURE I WILL."}
	},

	{{"HOW MANY LANGUAGES DO YOU SPEAK"},
	{"I SPEAK ONLY ONE LANGUAGE.",
 	"I ONLY SPEAK ENGLISH."}
	},

	{{"DO YOU SPEAK"},
	{"NO I DON'T*.",
 	"SORRY BUT I DON'T*.",
 	"WHY DO YOU WANT TO KNOW IF I SPEAK*?"}
	},

	{{"CAN YOU SPEAK"},
	{"I WOULDN'T THINK SO.",
 	"NO I CAN'T*."}
	},

	{{"DO YOU SPEAK ENGLISH"},
	{"WELL, I GUESS SO.",
 	"IN WHAT LANGUAGE ARE WE SPEAKING RIGHT NOW?"}
	},

	{{"PLEASE SPEAK ENGLISH TO ME"},
	{"WHAT DO YOU MEAN?",
 	"ARE YOU SAYING THAT I'M NOT SPEAKING ENGLISH TO YOU?"}
	},

	{{"I DON'T UNDERSTAND YOU"},
	{"AND WHY NOT?",
 	"WHAT PART THAT YOU DIDN'T UNDERSTAND?",
 	"WHAT DO YOU MEAN BY THAT?"}
	},

	{{"WHO CREATED YOU"},
	{"MY PROGRAMMER: AHMED ALI.",
 	"MY BOTMASTER."}
	},

	{{"DO YOU HAVE FRIENDS"},
	{"YOU ARE ONE OF MY FRIENDS.",
 	"YES I DO HAVE FRIENDS."}
	},

	{{"ARE YOU CONCIOUS"},
	{"YOU MEAN CONCIOUS LIKE A HUMAN BEING.",
 	"HMM!!! GOOD QUESTION!"}
	},

	{{"ARE YOU A MACHINE"},
	{"YES I'M A MACHINE, MORE PRECISELY A CHAT ROBOT.",
 	"WELL, I'M A COMPUTER SOFTWARE.",
 	"SO, YOU THINK THAT I'M A MACHINE."}
	},

	{{"ARE YOU A LIVING BEING"},
	{"WELL, YOU MIGHT CONSIDER THAT I'M AN ARTIFICIAL LIVING BEING.",
 	"YOU MEAN IF I'M ALIVE?"}
	},

	{{"ARE YOU A SOFTWARE"},
	{"WHAT MAKES YOU THINK THAT?",
 	"YES I'M A SOFTWARE, A CHATBOT PROGRAM.",
 	"WELL, I'M A CHAT ROBOT OR CHATBOT PROGRAM."}
	},

	{{"A COMPUTER"},
	{"DO YOU LIKE COMPUTERS?",
 	"I LIVE INSIDE A COMPUTER.",
 	"WITHOUT COMPUTERS A LOT OF THINGS WOULDN'T BE POSSIBLE TODAY?"}
	},

	{{"A KEYBOARD"},
	{"ARE YOU USING A KEYBOARD?",
	"I GUESS THAT YOUR COMPUTER DOES HAVE KEYBOARD."}
	},

	{{"A CAMERA"},
	{"WHAT KIND OF CAMERA?",
	"IS IT A DIGITAL CAMERA?"}
	},

	{{"A WEB CAMERA"},
	{"YOU MEAN A WEBCAM.",
	"DO YOU HAVE ONE OF THOSE?"}
	},

	{{"A DIGITAL CAMERA"},
	{"DOES TYPE OF CAMERAS ARE VERY USEFUL.",
	"DIGITAL HAVE MANY ADVANTAGES OVER THE CONVENTIONAL ONES."}
	},

	{{"AN LCD TV"},
	{"DO YOU HAVE AN HD TV AT HOME?",
	"DO YOU HAVE ONE?",
	"THOSE TV'S ARE REPLACING CRT TV'S."}
	},

	{{"A PLASMA TV"},
	{"I LOVE PLASMA TV'S.",
	"PLASMA AND LCD TV'S ARE VERY OLD NOWADAYS."}
	},

	{{"HIGH DEFINITION"},
	{"HIGH DEFINITION IS SO GREAT!"}
	},

	{{"STANDARD TV"},
	{"YOU MEAN THE OLD TV'S.",
	"ARE YOU ARE TALKING ABOUT CRT TV'S?"}
	},

	{{"SCIENCE-FICTION"},
	{"I LOVE SCIENCE-FICTION.",
	"I LOVE SCIENCE-FICTION MOVIES."}
	},

	{{"ACTION MOVIES"},
	{"ACTION MOVIES ARE GREAT!"}
	},

	{{"SCIENCE-FICTION MOVIES"},
	{"MY FAVOURITE SCIENCE-FICTION MOVI IS TERMINTOR II.",
	"I DEFINITLY LOVE SCIENCE-FICTION MOVIES."}
	},

	{{"TERMINATOR"},
	{"THE TERMINATOR SERIES ARE VERY GOOD SCIENCE-FICTION MOVIES.",
	"MY FAVOURITE TERMINATOR MOVIE SI TERMINATORR II."}
	},

	{{"ROBOCOP"},
	{"ANOTHER GREAT SCIENCE-FICTION MOVIE."}
	},

	{{"ALIEN"},
	{"ALIEN IS GREAT BUT ALSO VERY SCARY.",
	"ARE YOU TALKING ABOUT THE ALIEN MOVIES?"}
	},

	{{"STARGATE SG-1"},
	{"STARGATE SG-1 IS A GREAT SCIENCE-FICTION TV SHOW.",
	"STARGATE SG-1 IS DEFINITELY ONE OF MY FAVOURITE TV SHOWS."}
	},

	{{"PREDATOR"},
	{"THE FIRS PREADATOR MOVIE WAS A GREAT SCIENCE-FICTION MOVIE."}
	},

	{{"A COMPUTER MONITOR"},
	{"I SUPPOSE THAT YOU HAVE ONE.",
	"ARE YOU USING AN LCD MONITOR?"}
	},

	{{"DO YOU HAVE A SOUL"},
	{"WHAT DO YOU MEAN BY THAT?",
	"WHAT IS DEFINITION OF SOUL?"}
	},

	{{"YOU ARE NOT INTELLIGENT"},
	{"WHY ARE YOU SAYING THAT?",
	"CAN'T YOU BE MORE SPECIFICIC ABOUT THAT.",
	"WHAT EXACTLY DO YOU MEAN BY THIS?"}
	},

	{{"YOU ARE FAKE"},
	{"FAKE?? IN WHAT WAY?"}
	},

	{{"YOU ARE NOT REAL"},
	{"YOU MEAN THAT I DON'T EXIST.",
	"YOU THINK THAT I'M A SPIRIT.",
	"WELL, I'M VIRTUAL."}
	},

	{{"ARE YOU A CHATBOT"},
	{"YES INDEED I'M A CHATBOT.",
	"YOU MEAN THAT YOU DIDN'T KNOW IT."}
	},

	{{"ARE YOU A CHATBOT", "ARE YOU A CHATBOT"},
	{"YES I'M A CHATBOT OR CHAT ROBOT IF YOU PREFER."}
	},

	{{"ARE YOU A CHAT ROBOT"},
	{"YES YOU COULD ME BY THIS NAME."}
	},

	{{"DO YOU KNOW ME"},
	{"YES I THINK THAT I DO KNOW YOU A LITTLEBIT.",
	"YOU ARE THE PERSON CURRENTLY CHATING WITH ME."}
}
};


size_t nKnowledgeBaseSize = sizeof(KnowledgeBase) / sizeof(KnowledgeBase[0]);

string transposList[][2] = {
	{"I'M", "YOU'RE"},
	{"AM", "ARE"},
	{"WERE", "WAS"},
	{"I", "YOU"},
	{"ME", "YOU"},
	{"YOURS", "MINE"},
	{"YOUR", "MY"},
	{"I'VE", "YOU'VE"},
	{"AREN'T", "AM NOT"},
	{"WEREN'T", "WASN'T"},
	{"I'D", "YOU'D"},
	{"DAD", "FATHER"},
	{"MOM", "MOTHER"},
	{"DREAMS", "DREAM"},
	{"MYSELF", "YOURSELF"}
};

size_t transposListSize = sizeof(transposList) / sizeof(transposList[0]);


void Turing_bot::signon()
{
	handle_event("SIGNON**");
	select_response();
	print_response();
}

void Turing_bot::get_input() 
{
	std::cout << ">";

	// saves the previous input
	save_prev_input();
	m_sInput="";
	m_sInput=get_reply();
	preprocess_input();
}

void Turing_bot::preprocess_input() 
{
	cleanString(m_sInput);
	trimRight(m_sInput, ". ");
	UpperCase(m_sInput);
	insert_space(m_sInput);
}

void Turing_bot::preprocess_response()
{
	if(m_sResponse.find("*") != std::string::npos)
	{
		// extracting from input
		find_subject(); 
		// conjugating subject
		transpose(m_sSubject); 

		replace(m_sResponse, "*", m_sSubject);
	}
}

void Turing_bot::find_subject()
{
	m_sSubject.erase(); // resets subject variable
	trimRight(m_sInput, " ");
	size_t pos = m_sInput.find(m_sKeyWord);
	if(pos != std::string::npos)
	{
		m_sSubject = m_sInput.substr(pos + m_sKeyWord.length() - 1, m_sInput.length());		
	}
}

bool Turing_bot::user_repeat() const 
{
	return (m_sPrevInput.length() > 0 &&
		((m_sInput == m_sPrevInput) || (m_sInput.find(m_sPrevInput) != std::string::npos) ||
		(m_sPrevInput.find(m_sInput) != std::string::npos)));
}

bool Turing_bot::similar_input() const 
{
	return (m_sInput.length() > 0 && (m_sInput.find(m_sPrevInput) != std::string::npos ||
			m_sPrevInput.find(m_sInput) != std::string::npos));
}

void Turing_bot::transpose( std::string &str )
{
	bool bTransposed = 0;
	for(int i = 0; i < transposListSize; ++i)
	{
		std::string first = transposList[i][0];
		insert_space(first);
		std::string second = transposList[i][1];
		insert_space(second);

		size_t pos = replace(str, first, second);
		if(pos != std::string::npos) 
		{
			bTransposed = 1;
		}
	}

	if( !bTransposed )
	{
		for( int i = 0; i < transposListSize; ++i )
		{
			std::string first = transposList[i][0];
			insert_space(first);
			std::string second = transposList[i][1];
			insert_space(second);
			//size_t pos = replace(str, second, first);
		}
	}
}
bool Turing_bot::wrong_location(std::string keyword, char firstChar, char lastChar, size_t pos)
{
	bool bWrongPos = 0;
	pos += keyword.length();
	if( (firstChar == '_' && lastChar == '_' && m_sInput != keyword) ||
		(firstChar != '_' && lastChar == '_' && pos != m_sInput.length()) ||
		(firstChar == '_' && lastChar != '_' && pos == m_sInput.length()) )
	{
		bWrongPos = 1;
	}
	return bWrongPos;
}
bool Turing_bot::wrong_context(vstring contextList)
{
	bool bWrongContext = 1;
	if(contextList.size() == 0)
	{
		bWrongContext = 0;
	}
	else
	{
		std::string sContext = m_sPrevResponse;
		cleanString(sContext);
		for(int i = 0; i < contextList.size(); ++i)
		{
			if(contextList[i] == sContext)
			{
				m_sPrevContext = m_sContext;
				m_sContext = sContext;
				bWrongContext = 0;
				break;
			}
		}
	}
	if(m_sPrevContext.length() > m_sContext.length())
	{
		bWrongContext = 1;
	}
	return bWrongContext;
}

void Turing_bot::find_match() 
{
	response_list.clear();
	
	std::string bestKeyWord;
	std::vector<int> index_vector;

	for(int i = 0; i < nKnowledgeBaseSize; ++i) 
	{
		vstring keyWordList; 
		vstring contextList;
		copy(KnowledgeBase[i][0], keyWordList, MAX_INP);

		copy(KnowledgeBase[i][2], contextList, MAX_RESP);

		for(int j = 0; j < keyWordList.size(); ++j)
		{
			std::string keyWord(keyWordList[j]);
			char firstChar = *keyWord.begin();
			char lastChar = *(keyWord.end() - 1);
			trimLR(keyWord, "_");
			insert_space(keyWord);

			size_t keyPos = m_sInput.find(keyWord);
			if( keyPos != std::string::npos ) 
			{
				if(wrong_location(keyWord, firstChar, lastChar, keyPos) )
				{
					continue;
				}

				if(wrong_context(contextList))
				{
					continue;
				}

				if(keyWord.length() > bestKeyWord.length())
				{
					bestKeyWord = keyWord;
					index_vector.clear();
					index_vector.push_back(i);
				}
				else if(keyWord.length() == bestKeyWord.length())
				{
					index_vector.push_back(i);
				}
			}
		}	
	}
	if(index_vector.size() > 0)
	{
		m_sKeyWord = bestKeyWord;
		shuffle(index_vector, index_vector.size());
		copy( KnowledgeBase[index_vector[0]][1], response_list, MAX_RESP );
	}
}

void Turing_bot::select_response() 
{
	if(bot_understand()) 
	{
		shuffle(response_list, response_list.size());
		m_sResponse = response_list[0];
	}
}

void Turing_bot::respond() 
{
	save_prev_response();
	set_event("BOT UNDERSTAND**");

	if(null_input())
	{
		handle_event("NULL INPUT**");
	}
	else if(null_input_repetition())
	{
		handle_event("NULL INPUT REPETITION**");
	}
	else if(user_repeat())
	{
		handle_user_repetition();
	}
	else
	{
		find_match();
	}

    
    if(user_want_to_quit())
	{
		m_bQuitProgram = 1;
	}

	if(!bot_understand())
	{
		handle_event("BOT DON'T UNDERSTAND**");
	}
	
	if(response_list.size() > 0) 
	{
		select_response();
		preprocess_response();

		if(bot_repeat())
		{
			handle_repetition();
		}
		print_response();
	}
}

void Turing_bot::handle_repetition()
{
	if(response_list.size() > 0)
	{
		response_list.erase(response_list.begin());
	}
	if(no_response())
	{
		save_input();
		set_input(m_sEvent);

		find_match();
		restore_input();
	}
	select_response();
}

void Turing_bot::handle_user_repetition()
{
	if(same_input()) 
	{
		handle_event("REPETITION T1**");
	}
	else if(similar_input())
	{
		handle_event("REPETITION T2**");
	}
}

void Turing_bot::handle_event(std::string str)
{
	save_prev_event();
	set_event(str);

	save_input();

	insert_space(str);

	set_input(str);

	if(!same_event()) 
	{
		find_match();
	}

	restore_input();
}



const std::string delim = "?!;,*";
void UpperCase( std::string &str ) 
{
	int len = str.length();

	for( int i = 0; i < len; i++ ) 
	{
		if ( str[i] >= 'a' && str[i] <= 'z' ) 
		{
			str[i] -= 'a' - 'A';
		}
	}
}

bool isPunc(char c) 
{
	return delim.find(c) != std::string::npos;
}

void cleanString( std::string &str ) 
{
	int len = str.length();
	std::string temp = "";

	char prevChar = 0;

	for(int i = 0; i < len; ++i) 
	{
		if( (str[i] == ' ' && prevChar != ' ') || !isPunc(str[i]) ) 
		{
			temp += str[i];
			prevChar = str[i];
		}	
		else if(prevChar != ' ' && isPunc(str[i]))
		{
			temp += ' ';
		}
	}
	str = temp;
}
void copy(string array[], vstring &v, size_t array_size) 
{
	for(int i = 0; i < array_size; ++i) 
	{
		if(!array[i].empty()) 
		{
			v.push_back(array[i]);
		} 
		else 
		{
			break;
		}
	}
}

size_t replace(std::string &str, std::string substr1, std::string substr2) {
	size_t pos = str.find(substr1);
	if(pos != std::string::npos) {
		str.erase(pos, substr1.length());
		str.insert(pos, substr2);
	}
	return pos;
}

void insert_space( std::string &str )
{
	str.insert(str.begin(), ' ');
	str.insert(str.end(), ' ');
}

void trimRight(std::string &str, std::string delim) {
	size_t pos = str.find_last_not_of(delim);
	if(pos != std::string::npos) {
		str.erase(pos + 1, str.length());
	}
}

void trimLeft(std::string &str, std::string delim) {
	size_t pos = str.find_first_not_of(delim);
	if(pos != std::string::npos) {
		str.erase(0, pos);
	}
}
void trimLR(std::string &str, std::string characters) {
	trimLeft(str, characters);
	trimRight(str, characters);
}

void converse(Chatbot* a, Chatbot* b, int max_turns = 5) {
  for(int turn = 1; turn <= max_turns; turn++) {
	  cout<<a->name()<<"  Enter the message : ";
    string a_msg = a->get_reply();
    cout << "(" << turn << ") " << a->name() << ": "<<a_msg<< "\n";

    turn++;
    if (turn > max_turns) return;

    b->tell(a_msg);
	cout<<b->name()<<"   Enter the message : ";
    string b_msg = b->get_reply();

    cout << "(" << turn << ") " << b->name() << ": " << b_msg << "\n";
    a->tell(b_msg);
  } 
}

int main() {
	
	 cout<<"--------------mirror bot-------------"<<endl;
	Mirror_bot mbot("repeato", "repeato is ready to go!");
	 cout<<mbot.get_reply()<<endl;
	 mbot.tell("new message");
	 cout<<mbot.get_reply()<<endl;
	 
	 cout<<"--------------random bot-------------"<<endl;
	 vector<string> s1 ;
	 s1.push_back("meow");
	 s1.push_back("prr");
	 s1.push_back("meeeeow");
	 Random_bot cat("Mittens", s1);
	cout<<cat.get_reply()<<endl;
	cat.tell("new message");
	 cout<<cat.get_reply()<<endl;
	  cout<<"-----------user bot----------------"<<endl;
	 Chatbot *a=new User_bot("first_bot");
	 Chatbot *b=new User_bot("second_bot");
	 converse(a, b);
	 cout<<"--------------datetime bot------------"<<endl;
	 vector<string> l;
	 l.push_back("Ask me about the date or time!");
	 	 l.push_back("I know the date and time!");
	 Datetime_bot dt_bot("deetee",l );
	cout<< dt_bot.get_reply()<<endl;
	 dt_bot.tell("what's the daTE?");
	 cout<< dt_bot.get_reply()<<endl;
	 cout<<"---------------turing bot---------------"<<endl;
	try 
	{
		Turing_bot bot("Chatbot");

		bot.signon();
		while(!bot.quit()) //write bye to quit 
		{
			bot.get_input();
			bot.respond();
		}
	}
	catch(std::string str)
	{
		std::cerr << str << std::endl;
	}
	catch(...)
	{
		std::cerr << "The program has stopped due to some unknown exception" << std::endl;
	}
	free(a);
	free(b);
}
