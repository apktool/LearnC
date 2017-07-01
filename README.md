迁移原代码至子目录2016

```
git init LearnC && cd LearnC

echo "迁移原代码至子目录2016" > README.md

git add README.md
git commit -m "Archive all code by 2016" -s

git remote add other git@github.com:apktool/LearnC.git
git remote add origin git@github.com:apktool/LearnC.git

git subtree -P 2016 other master

git push
```
 *注*这种方法会导致所有原有commit被覆盖，但是却可以保证log完整。
 目前我还没有找到更好的方法
