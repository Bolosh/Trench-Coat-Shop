#pragma once
#include "Service.h"
#include "Repository.h"
#include "Repository.h"
#include <assert.h>

class Test {
private:
	TrenchCoat c1, c2;
	Repository r;
	Service s;

public:
	void testCoat() {
		c1.makeCoat(1, 1, (float)1.11, "red", "link");
		assert(c1.getSize() == 1);
		assert(c1.getQuantity() == 1);
		assert(c1.getPrice() == (float)1.11);
		assert(c1.getColour() == "red");
		assert(c1.getLink() == "link");
		c2.setSize(2);
		c2.setQuantity(2);
		c2.setPrice((float)2.22);
		c2.setColour("blue");
		c2.setLink("link2");
		assert(c2.getSize() == 2);
		assert(c2.getQuantity() == 2);
		assert(c2.getPrice() == (float)2.22);
		assert(c2.getColour() == "blue");
		assert(c2.getLink() == "link2");
	}

	void testRepo() {
		try {
			r.addCoat(c1);
			r.addCoat(c2);
		}
		catch (ExceptionClass) {
			assert(false);
		}
		assert(r.findExactCoat("link") != NULL);
		assert(r.findExactCoat("not_a_link") == NULL);
		assert(r.getCoat(0)->getLink() == c1.getLink());
		assert(r.length() == 2);
		try {
			r.removeCoat(c1);
		}
		catch (ExceptionClass) {
			assert(false);
		}
		try {
			r.removeCoat(c1);
		}
		catch (ExceptionClass) {
			assert(true);
		}
		assert(r.length() == 1);
		assert(r.searchCoat(c1) == -1);
		std::vector<TrenchCoat> v = r.getVector();
		assert(v.size() == 1);
	}

	void testService() {
		try {
			s.addCoat(c1);
			s.addCoat(c2);
		}
		catch (ExceptionClass) {
			assert(false);
		}
		assert(s.repoLength() == 2);
		assert(s.getCoat(0)->getLink() == c1.getLink());
		assert(s.findExactCoat("link") != NULL);
		assert(s.findExactCoat("not_a_link") == NULL);
		try {
			s.removeCoat(c2);
		}
		catch (ExceptionClass) {
			assert(false);
		}
		assert(s.repoLength() == 1);
		std::vector<TrenchCoat> v = s.getRepoData();
		assert(v.size() == 1);
	}

};