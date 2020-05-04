    On console, check to see if you have ssh files

ls -al ~/.ssh

If there are id_rsa and id_rsa.pub files, it’s been set up already

If not:

ssh-keygen -t rsa -b 4096 -C “h15200@gmail.com”
Click enter twice for the default names. Now you should have id_rsa which is the secret file, and id_rsa.pub which is the file you share with github, heroku to share info.

Start the ssh agent (if it’s already running, you get the pid #):

eval “\$(ssh-agent -s)”

Register to add identity

ssh-add -K ~/.ssh/id_rsa

On github - setting - add ssh
On terminal

cat ~/.ssh/id_rsa.pub
