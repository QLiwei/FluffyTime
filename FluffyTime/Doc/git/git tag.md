```shell
# 列出已有标签 -l --list 字母顺序列出标签
git tag

# 轻量标签很像一个不会改变的分支——它只是某个特定提交的引用。
# 附注标签是存储在 Git 数据库中的一个完整对象， 它们是可以被校验的，其中包含打标签者的名字、电子邮件地址、日期时间， 此外还有一个标签信息，并且可以使用 GNU Privacy Guard （GPG）签名并验证。 通常会建议创建附注标签，这样你可以拥有以上所有信息。但是如果你只是想用一个临时的标签， 或者因为某些原因不想要保存这些信息，那么也可以用轻量标签
# 创建附注标签
git tag -a v1.4 -m "my version 1.4"

# 显示标签信息和与之对应的提交信息
git show <tag>

# 创建轻量标签
git tag v1.4-lw
# 只显示提交信息
git show <tag>

# 后期打标签
git tag -a v1.2 <提交的校验和>

# 共享标签
git push <remote> <tagname>
# 不在服务器的所有标签上传
git push <remote> --tags

# 删除标签
git tag -d <tagname>
# 更新远程仓库
git push <remote> :refs/tags/<tagname>
git push <remote> --delete <tagname>
```

