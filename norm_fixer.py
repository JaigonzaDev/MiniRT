import os
import re

def fix_norm_file(filepath):
    with open(filepath, 'r') as f:
        content = f.read()

    lines = content.split('\n')
    new_lines = []
    
    for line in lines:
        # Preprocessor indenting:
        # MiniRT has #ifndef at root, so `#define` and `#include` inside should have `# define` and `# include`
        if line.startswith('#define '):
            line = '# define ' + line[8:]
        elif line.startswith('#include '):
            line = '# include ' + line[9:]
            
        # struct closures: '}   t_something;' -> '}\tt_something;'
        line = re.sub(r'^\}\s+(t_[a-zA-Z0-9_]+);', r'}\t\1;', line)
        
        # Space between type and name mapping (hacky but handles most cases)
        # e.g., 'double      diameter;' -> 'double\t\tdiameter;'
        # 'struct s_sphere *next;' -> 'struct s_sphere\t*next;'
        # Look for type (word or struct word) followed by spaces then variable name
        if not line.startswith('/*') and not line.startswith('**') and not line.startswith('*/'):
            line = re.sub(r'(double)\s+([a-zA-Z_*])', r'\1\t\t\2', line)
            line = re.sub(r'(int)\s+([a-zA-Z_*])', r'\1\t\t\2', line)
            line = re.sub(r'(char)\s+([a-zA-Z_*])', r'\1\t\t\2', line)
            line = re.sub(r'(t_[a-zA-Z0-9_]+)\s+([a-zA-Z_*])', r'\1\t\2', line)
            line = re.sub(r'(struct\s+[a-zA-Z0-9_]+)\s+([a-zA-Z_*])', r'\1\t\2', line)
            line = re.sub(r'(void)\s+([a-zA-Z_*])', r'\1\t\t\2', line)
            # Sometimes t_type needs 2 tabs if it's short, let's just do 1 tab for now. 
            
        new_lines.append(line)

    with open(filepath, 'w') as f:
        f.write('\n'.join(new_lines))

for root, _, files in os.walk("srcs"):
    for f in files:
        if f.endswith(".c") or f.endswith(".h"):
            fix_norm_file(os.path.join(root, f))
            
for root, _, files in os.walk("include"):
    for f in files:
        if f.endswith(".c") or f.endswith(".h"):
            fix_norm_file(os.path.join(root, f))
