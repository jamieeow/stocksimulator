/* data structure for the sample problem */

typedef char String20[21]; 

struct nameTag {
	String20 last;
	String20 first;
};

struct studentTag {
	int ID; // ID number
	struct nameTag name;
	float grade;	
};


