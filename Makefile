all: evalf

evalf: eval_formula.cpp Formula.hpp
	g++ $< -O2 -o $@
	##################
	#### examples ####
	##################
	./$@ "3+3"
	./$@ "-(4-5/2)"
	./$@ "4*-3"
	##################
	
	##################
	##### README #####
	##################
	cat README.md

.PHONY: test
test: unit_test.log

unit_test.log: unit_test
	./$< > $@

unit_test: test.cpp Formula.hpp
	g++ $< -O2 -o $@

st.log: evalf input.txt st.ans.log
	cat input.txt |xargs -L 1 ./$< > st.log

st.ans.log: input.txt
	cat input.txt |xargs -L 1 -i echo {} |bc > st.ans.log

clean: 
	rm -f evalf unit_test.log unit_test st.log st.ans.log
