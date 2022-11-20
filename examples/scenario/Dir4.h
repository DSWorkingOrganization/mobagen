#ifndef DIR4_H
#define DIR4_H

struct Dir4 {
public: 
	float dir[4];

	Dir4() { 
		dir[0] = 0;
        dir[1] = 0;
        dir[2] = 0;
        dir[3] = 0;
	}

	~Dir4() { 
        delete dir;
	}
};

#endif
