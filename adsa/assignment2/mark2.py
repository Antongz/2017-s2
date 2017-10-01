#!/usr/bin/python
import os

def silent_remove(filename):
    """Remove a file whether it exists or not"""
    try:
        os.remove(filename)
    except OSError:
        pass

def test_case(input_str, output_str):
    """Assume main.out exist"""
    assert os.path.isfile('main.out'), 'where is main.out?'
    silent_remove('tempinput')
    silent_remove('tempoutput')
    with open('tempinput', 'w') as fp:
        fp.write(input_str)
    assert os.path.isfile('tempinput'), 'fail to create tempinput'
    os.system('./main.out < tempinput > tempoutput')
    assert os.path.isfile('tempoutput'), 'fail to create tempoutput'
    with open('tempoutput') as fp:
        output_str_actual = fp.read()
    if output_str_actual.strip() != output_str.strip():
        print "For input ", input_str
        print "Output received ", output_str_actual
        print "Output shouldbe ", output_str
        print ""

assert os.path.isfile('main.cpp'), 'main.cpp does not exist'
silent_remove('main.out')
os.system('g++ -std=c++11 -o main.out -O2 -Wall main.cpp')
assert os.path.isfile('main.out'), 'does not compile'
assert os.path.isfile('test.txt'), 'test.txt does not exist'

with open('test.txt') as fp:
    for line in fp:
        terms = line.split()
        if not terms:
            print "Saw an empty line"
            continue
        modi_count = 0
        finish_count = 0
        reached_output = False
        for term in terms:
            if term in ["IN", "PRE", "POST"]:
                finish_count += 1
                reached_output = True
                continue
            if not reached_output:
                assert term[0] == "A" or term[0] == "D", "Must start with A/D"
                val = int(term[1:])
                assert 1 <= val <= 100, "val must be between 1 and 100"
                modi_count += 1
            else:
                if term == "EMPTY":
                    continue
                val = int(term)
                assert 1 <= val <= 100, "val must be between 1 and 100"
        assert 1 <= modi_count <= 100, "should have 1-100 modification moves"
        assert finish_count == 1, "should have exactly 1 finishing move"
        test_case(" ".join(terms[:modi_count+1]), " ".join(terms[modi_count+1:]))

print "That's it! I have reached the end of your test.txt."
print "Warning!!! This script only performs minimal format checking."
