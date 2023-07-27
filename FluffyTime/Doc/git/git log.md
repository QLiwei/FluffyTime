```shell
git log

# -p --patch 显示每次提交所引入的差异 
# -2 显示最近几次提交
git log -p -2

# --stat 提交的简略统计信息
git log --stat

# --pretty 不同于默认格式的方式展示提交历史
# oneline 一行显示一个提交
# short
# full
# fuller
git log --pretty=
# format
# %H	提交的完整哈希值
# %h	提交的简写哈希值
# %T	树的完整哈希值
# %t	树的简写哈希值
# %P	父提交的完整哈希值
# %p	父提交是简写哈希值
# %an	作者名字
# %ae	作者邮箱地址
# %ad	作者的修订日期 --date 定制格式
# %ar	作者修订日期，按多久以前的方式显示
# %cn	提交者的名字
# %ce	提交者的邮箱地址
# %cd
# %cr
# %s 	提交说明
git log --pretty=format:"%h - %an, %ar : %s"

# --graph
git log --pretty=format:"%h %s" --graph

# 限制输出长度 
# --since 
# --until
# 最近两周
git log --since=2.weeks
# --author
# --grep
```

- -p 按补丁格式显示每个提交引入的差异。
- --stat 显示每次提交的文件修改统计信息。
- --shortstat 只显示 --stat 中最后的行数修改添加移除统计。
- --name-only 仅在提交信息后显示已修改的文件清单。
- --name-status 显示新增、修改、删除的文件清单。
- --abbrev-commit 仅显示 SHA-1 校验和所有 40 个字符中的前几个字符。
- --relative-date 使用较短的相对时间而不是完整格式显示日期（比如“2 weeks ago”）。
- --graph 在日志旁以 ASCII 图形显示分支与合并历史。
- --pretty 使用其他格式显示历史提交信息。可用的选项包括 oneline、short、full、fuller 和
- format（用来定义自己的格式）。
- --oneline --pretty=oneline --abbrev-commit 合用的简写。



限制 git log 输出的选项

- -<n> 仅显示最近的 n 条提交。
- --since, --after 仅显示指定时间之后的提交。
- --until, --before 仅显示指定时间之前的提交。
- --author 仅显示作者匹配指定字符串的提交。
- --committer 仅显示提交者匹配指定字符串的提交。
- --grep 仅显示提交说明中包含指定字符串的提交。
- -S 仅显示添加或删除内容匹配指定字符串的提交。

