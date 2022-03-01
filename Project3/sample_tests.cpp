#include "gtest/gtest.h"
#include "UTString.h"


TEST(Test01, simpleTest1) {
	char p[12];
	const char* q = "Hello World";
	UTString* s; 
	UTString* t; 
	unsigned k;
	
	for (k = 0; k < 12; k += 1) {
		p[k] = q[k];
	}
	s = utstrdup(p);
	
	ASSERT_EQ(0, strcmp(s->string, "Hello World"));

	q = "you goofed!";
	for (k = 0; k < 12; k += 1) {
		p[k] = q[k];
	}
	ASSERT_EQ(0, strcmp(s->string, "Hello World"));
	
	t = utstrdup(s->string);
	utstrfree(s);

	ASSERT_EQ(0, strcmp(t->string, "Hello World"));	
	utstrfree(t);
}

TEST(Test02, simpleTest2) {
	char c_str1[20] = "hello";
	UTString* ut_str1;
	UTString* ut_str2;

	strcat(c_str1, " world");

	ut_str1 = utstrdup("hello ");
	ut_str1 = utstrrealloc(ut_str1, 20);
	utstrcat(ut_str1, c_str1);
	ASSERT_EQ(0, strcmp(ut_str1->string, "hello hello world"));	

	utstrcat(ut_str1, " world");
	ASSERT_EQ(0, strcmp(ut_str1->string, "hello hello world wo"));	

	ut_str2 = utstrdup("");
	ut_str2 = utstrrealloc(ut_str2, 11);
	utstrcpy(ut_str2, ut_str1->string + 6);
	ASSERT_EQ(0, strcmp(ut_str2->string, "hello world"));	

	ut_str2 = utstrrealloc(ut_str2, 23);
	utstrcat(ut_str2, " ");
	utstrcat(ut_str2, ut_str1->string);
	ASSERT_EQ(0, strcmp(ut_str2->string, "hello world hello hello"));
 
	utstrfree(ut_str1);
	utstrfree(ut_str2);
}

/**
 * Regarding utstrfree():
 * There is no way to test utstrfree() without making assumptions,
 * so it will be tested using Valgrind and the combined tests.
 */


TEST(Test08, bigStrings) {
	int k;
	UTString* ut_str1 = utstrdup("");
	ut_str1 = utstrrealloc(ut_str1, BIG); // big, big string

	for (k = 0; k < BIG; k += 1) {
		utstrcat(ut_str1, "*");
	}
	ASSERT_EQ('*', ut_str1->string[BIG-1]);
	ASSERT_EQ(BIG, strlen(ut_str1->string));

	utstrfree(ut_str1);	
}
