input = """
a :- not b.
b :- not a.

s :- not a.
s :- not b.
"""
output = """
a :- not b.
b :- not a.

s :- not a.
s :- not b.
"""
