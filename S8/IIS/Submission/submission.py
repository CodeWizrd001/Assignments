import re

# Regex for pattern matching +++.string

reg = re.compile(r'\+\+\+[a-zA-Z0-9_\,\.]+')

# Read Template.md
text = open('Template.md', 'r').read()
print(text)

matches = reg.findall(text)

print(matches)

for match in matches:
    print(match)
    fName = match.split(',')[1]
    print(f'[+] Replacing File: {fName}')
    text = text.replace(match, open(fName, 'r').read())

outputFilename = "B180341CS_AJAY_Assig2.md"
out = open(outputFilename, 'w')
out.write(text)
out.close()