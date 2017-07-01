迁移原代码至子目录2016

```
git init LearnC && cd LearnC

echo "迁移原代码至子目录2016" > README.md

git add README.md
git commit -m "Archive all code by 2016" -s

git remote add other git@github.com:apktool/LearnC.git
git subtree -P 2016 other master

git push
```
