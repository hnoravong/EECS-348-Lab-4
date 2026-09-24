# AI Usage Log — Addendum (Debugging & Setup Help)

**Tool used:** Claude (Anthropic)

This addendum covers a follow-up session where I asked for help running my
compiled program, debugging an issue, and setting up GitHub — separate from
the original request to write `task1.c`/`task2.c`.

## 1. "Program name not found" error when running the executable
I pasted a terminal error where I had accidentally typed a placeholder
string (`"enter program name, for example ..."`) directly into the shell
instead of an actual command. Claude explained that this was example text,
not a command to run, and walked me through the correct steps:
- Compile with `gcc task1.c -o task1` (or `make all` if using the Makefile).
- Run the executable with `./task1` (the `./` prefix is required).
- Suggested running `ls` to check what files actually existed in the
  directory before guessing further.

## 2. Entering `1` didn't stop the program
I reported that typing `1` at the score prompt didn't exit the loop as
expected. Since I hadn't yet pasted the specific code causing it, Claude
asked clarifying questions (whether this was the same Lab 8 code or a
different Lab 4 assignment, what exactly happened on input, and asked me to
paste the relevant loop/condition) and listed the most common causes of
this bug for me to check:
- Using `=` (assignment) instead of `==` (comparison) in the exit check.
- The `break`/exit check being misplaced relative to the loop.
- Leftover/bad input in the input buffer from a prior `scanf` causing the
  comparison to run against garbage or an unset variable.

## 3. How to connect to a GitHub repo
I asked generally how to connect to a GitHub repository. Claude gave
instructions for both directions:
- **Cloning an existing repo:** `git clone https://github.com/username/repo-name.git`.
- **Pushing local files to a new repo:** `git init`, `git add .`,
  `git commit -m "..."`, `git branch -M main`,
  `git remote add origin <url>`, `git push -u origin main`.
- Noted that GitHub requires a Personal Access Token (or SSH) instead of a
  plain password for HTTPS pushes.

## 4. Compiler error: `swtich (to) {`
I pasted a compiler error (`implicit declaration of function 'swtich'`,
`expected ';' before '{' token`) from my own edited copy of `task2.c`.
Claude identified this as a one-letter typo — `swtich` should be `switch`
— and gave the corrected line, then reminded me to rerun `make clean` and
`make all` afterward.

## 5. Connecting to GitHub via SSH
I asked what to do differently if connecting over SSH instead of HTTPS.
Claude walked through:
- Checking for an existing key (`ls -al ~/.ssh`).
- Generating a new key if needed (`ssh-keygen -t ed25519 -C "email"`).
- Starting the SSH agent and adding the key (`ssh-agent`, `ssh-add`).
- Copying the public key (`cat ~/.ssh/id_ed25519.pub`) and adding it under
  GitHub → Settings → SSH and GPG keys.
- Testing the connection (`ssh -T git@github.com`).
- Cloning/connecting using the SSH-style URL
  (`git@github.com:username/repo-name.git`) instead of the HTTPS URL, and
  how to switch an existing remote from HTTPS to SSH with
  `git remote set-url origin <ssh-url>`.
- Noted that an SSH key set up on the shared lab computer is tied to that
  machine and would need to be re-added if I switch computers.

## What I verified/changed myself
- Applied the `swtich` → `switch` fix to my own local copy of `task2.c` and
  recompiled to confirm the warning/error were gone.
- Confirmed on my own machine/lab computer whether an SSH key already
  existed before generating a new one.
- Still need to identify and fix the actual root cause of the "entering 1
  doesn't stop the program" bug in my own code, since I hadn't yet pasted
  the specific loop for Claude to review.
