#!/usr/bin/python
import os
import string
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

def check_key(key):
    assert 1 <= len(key) <= 10, "key size must be between 1 and 10"
    assert all(c in string.ascii_lowercase for c in key), "key should only contain lower case letters"

with open('test.txt') as fp:
    for line in fp:
        terms = line.split()
        if not terms:
            print "Saw an empty line"
            continue
        modi_count = 0
        for term in terms:
            if term[0] == "A" or term[0] == "D":
                key = term[1:]
                check_key(key)
                modi_count += 1
        assert 1 <= modi_count <= 26, "should have 1-26 modification moves"
        for key in terms[modi_count:]:
            check_key(key)
        test_case(" ".join(terms[:modi_count]), " ".join(terms[modi_count:]))

print "That's it! I have reached the end of your test.txt."
print "If you don't see any errors, then that means your format is mostly correct."
print "Warning!!! This script only performs minimal format checking."
