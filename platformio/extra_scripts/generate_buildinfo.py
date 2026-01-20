import os
from datetime import datetime
Import("env")

header_path = os.path.join(env['PROJECT_SRC_DIR'], 'build_info.h')

# Target dir for generated files (won't pollute src/)
os.makedirs(os.path.dirname(header_path), exist_ok=True)

# Current formatted timestamp (match your Utils::formatBuildTimestamp logic)
now = datetime.now()
timestamp_str = now.strftime('%Y-%m-%d %H:%M:%S')  # Customize format as needed

content = f'''#ifndef BUILD_INFO_H
#define BUILD_INFO_H

#define BUILD_TIMESTAMP_STR "{timestamp_str}"

#endif
'''

# Only write if content changed (key for incremental builds)
try:
    with open(header_path, 'r') as f:
        old_content = f.read()
except FileNotFoundError:
    old_content = None  # First build: always create

if old_content != content:
    with open(header_path, 'w') as f:
        f.write(content)
    print(f"Updated build_info.h: {timestamp_str}")
else:
    print("build_info.h unchanged, skipping write")
