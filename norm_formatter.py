import os, re

HEADER_TEMPLATE = """/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   {filename:<46}:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */"""

def process_file(filepath):
    with open(filepath, 'r') as f:
        content = f.read()

    # Skip if header already exists
    if content.startswith("/* ************************************************************************** */"):
        lines = content.split('\n')
        content = '\n'.join(lines[11:])

    new_lines = []
    for line in content.split('\n'):
        # leading spaces to tabs (1 tab = 4 spaces)
        match = re.match(r'^( +)', line)
        if match:
            spaces = match.group(1)
            num_spaced = len(spaces)
            tabs = '\t' * (int(num_spaced / 4))
            rem = ' ' * (num_spaced % 4)
            line = tabs + rem + line[num_spaced:]
            
        new_lines.append(line)

    content = '\n'.join(new_lines)
    
    filename = os.path.basename(filepath)
    if len(filename) > 42:
        filename = filename[:42]
    header = HEADER_TEMPLATE.format(filename=filename)
    
    new_content = header + '\n' + content.lstrip()

    with open(filepath, 'w') as f:
        f.write(new_content)

for root, _, files in os.walk("srcs"):
    for f in files:
        if f.endswith(".c") or f.endswith(".h"):
            process_file(os.path.join(root, f))
            
for root, _, files in os.walk("include"):
    for f in files:
        if f.endswith(".c") or f.endswith(".h"):
            process_file(os.path.join(root, f))
