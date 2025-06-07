#include<iostream>

#define MAXLEN 255

struct String {
	char ch[MAXLEN + 1];
	int size{ 0 };
};

void strAssign(String& s, const char* chars) {
	s.size = 0;
	for (int i = 0; chars[i] != '\0'; ++i) {
		s.ch[i] = chars[i];
		s.size++;
	}
}

void strCopy(String& s, const String s1) {
	s = s1;
}

bool strEmpty(String& s) {
	return s.size == 0;
}

int strCompare(String& s, String& s1) {
	int n = std::min(s.size, s1.size);
	for (int i = 0; i < n; ++i) {
		if (s.ch[i] < s1.ch[i]) {
			return -1;
		} else if (s.ch[i] > s1.ch[i]) {
			return 1;
		}
	}
	return 0;
}

int strLength(String& s) {
	return s.size;
}

void clearString(String& s) {
	s.size = 0;
}

//用s返回由s1和s2联接而成的新串
void concat(String& s, String& s1, String& s2) {
	for (int i = 0; i < s1.size; ++i) {
		s.ch[i] = s1.ch[i];
	}
	for (int i = 0; i < s2.size; ++i) {
		s.ch[i + s1.size] = s2.ch[i];
	}
	s.size = s1.size + s2.size;
}

void subString(String& s, String& s1, int pos, int len) {
	for (int i = 0; i < len; ++i) {
		s.ch[i] = s1.ch[i + pos];
	}
	s.size = len;
}

//在串s的下标为pos的字符之前插入串s1
void strInsert(String& s, int pos, String& s1) {
	if (pos >= s.size) {
		std::cout << "插入位置不合理" << std::endl;
		return;
	}
	for (int i = s.size + s1.size - 1; i >= s1.size + pos; --i) {
		s.ch[i] = s.ch[i - s1.size];
	}
	for (int i = pos; i < pos + s1.size; ++i) {
		s.ch[i] = s1.ch[i - pos];
	}
	s.size += s1.size;
}

//从串s中删除下标为pos的字符起长度为len的子串
void strDelete(String& s, int pos, int len) {
	if (pos > s.size - len) {
		std::cout << "删除位置不合理" << std::endl;
		return;
	}
	for (int i = pos; i < pos + len; ++i) {
		s.ch[i] = s.ch[i + len];
	}
	s.size -= len;
}

void destroyString(String& s) {
	delete(s.ch);
}

void printString(String& s) {
	for (int i = 0; i < s.size; ++i) {
		std::cout << s.ch[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	String s;
	s.ch[0] = 'a';
	s.ch[1] = 'b';
	s.ch[2] = 'c';
	s.size = 3;

	std::cout << "--------|s1|--------" << std::endl;
	String s1;
	strAssign(s1, "ddbbc");
	strInsert(s1, 1, s);
	printString(s1); //d a b c d b b c
	strDelete(s1, 2, 3);
	printString(s1); //d a b b c
	std::cout << strLength(s1) << std::endl; //5
	std::cout << strEmpty(s1) << std::endl; //false

	std::cout << "--------|s2|--------" << std::endl;
	String s2;
	strCopy(s2, s1); //d a b b c
	printString(s2);

	std::cout << "--------|s3|--------" << std::endl;
	String s3;
	concat(s3, s, s2); 
	printString(s3); //a b c d a b b c

	std::cout << "--------|s4|--------" << std::endl;
	String s4;
	subString(s4, s3, 2, 4);
	printString(s4); //c d a b
	std::cout << strCompare(s4, s3) << std::endl; //true
	clearString(s4);
	std::cout << strLength(s4) << std::endl; //0
	return 0;
}

//strAssign
//strCopy
//strEmpty
//strCompare
//strLength
//clearString
//concat
//subString
//strInsert
//strDelete
//destroyString
//printString