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
    if output_str_actual.split() != output_str.split():
        print "For input ", input_str
        print "Output received ", output_str_actual
        print "Output shouldbe ", output_str
        print ""

assert os.path.isfile('main.cpp'), 'main.cpp does not exist'
silent_remove('main.out')
os.system('g++ -o main.out -O2 -Wall main.cpp')
assert os.path.isfile('main.out'), 'does not compile'
assert os.path.isfile('test.txt'), 'test.txt does not exist'

with open('test.txt') as fp:
    for line in fp:
        terms = line.split()
        if not terms:
            break
        assert len(terms) == 5, "Need exactly 5 numbers: " + line
        for term in terms:
            assert set(term) <= set("0123456789"), "Only 0-9 allowed: " + line
        test_case(" ".join(terms[:3]), " ".join(terms[3:]))

print "That's it! I have reached the end of your test.txt."
