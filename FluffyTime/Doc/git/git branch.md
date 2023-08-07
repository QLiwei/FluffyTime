```shell
$ git add README test.rb LICENSE
$ git commit -m 'The initial commit of my project'
```

![首次提交对象及其树结构。](https://git-scm.com/book/en/v2/images/commit-and-tree.png)

![提交对象及其父对象。](https://git-scm.com/book/en/v2/images/commits-and-parents.png)

- blod对象：保存文件快照
- tree对象：记录目录结构和blod对象索引
- commit对象：tree对象指针，父对象，提交信息

### **分支创建：**

```shell
$ git branch [branch-name]
```

> 特殊指针：HEAD 指向当前所在分支
>
> 查看各个分支当前所指的对象
>
> git log --oneline --decorate

### **分支切换：**

```SHELL
$ git checkout [branch-name]
```

> 查看分叉历史
>
> git log --oneline --decorate --graph --all
>
> 构建分支并切换至构建的分支
>
> git checkout -b [branch-name]

### **分支合并：**

```shell
$ git checkout master
$ git merge iss53
# 如有冲突，解决冲突
$ git branch -d iss53
# 完成合并提交
$ git commit 
```

> 图像化工具解决冲突 
>
> git mergetool

![一次典型合并中所用到的三个快照。](https://git-scm.com/book/en/v2/images/basic-merging-1.png)



### **分支管理：**

```SHELL
# 显示本地分支
$ git branch
 iss53
*master
 testing
# 查看每个分支的最后一次提交
$ git branch -v
# 查看哪些已经合并到当前分支 没有*号的分支通常可以git branch -d 删除
$ git branch --merged
# 查看所有包含未合并到当前分支工作的分支 使用git branch -d 删除时会失败
$ git branch --no-mered
```

> *HEAD指针所指的分支
>
> git branch -D 强制删除分支

## 分支开发工作流

### 长期分支：

- master 分支：保留完全稳定的代码——有可能仅仅是已经发布或即将发布的代码  
- develop next分支：后续开发或者测试稳定性 ——这些分支不必保持绝对稳定，但是一旦达到稳定状态，它们就可以被合并入 master 分支了  
- proposed（建议） 或 pu: proposedupdates（建议更新）分支 ：使你的分支具有不同级别的稳定性；当它们具有一定程度的稳定性后，再把它们合并入具有更高级别稳定性的分支中。  

### 主题分支：

主题分支是一种短期分支，它被用来实现单一特性或其相关工作  



### 远程分支：

远程引用是对远程仓库的引用（指针），包括分支、标签。

远程跟踪分支是远程分支状态的引用。它们是你无法移动的本地引用。一旦你进行了网络通信， Git 就会为你移动它们以精确反映远程仓库的状态。

```shell
# 获取远程引用的完整列表
$ git ls-remote <remote>
# 获取远程分支的更多信息
$ git remote show <remote>
```

> 远程仓库名字"origin"与分支名字"master"一样，在Git并没有特殊含义，是Git默认名字
>
> "master" git init 时默认的起始分支名字
>
> "origin" git clone 默认的远程仓库名字
>
> git clone -o [rep-name]  rep-anme/master

**同步远程仓库数据**

```shell
$ git fetch <remote>
```

```shell
# 添加远程仓库引用到当前项目
$ git remote add <remote> <url>
```

#### **推送**

```shell
$ git push <remote> <branch>
```

> 这里有些工作被简化了。 Git 自动将 <branch> 分支名字展开  
>
> 要特别注意的一点是当抓取到新的远程跟踪分支时，本地不会自动生成一份可编辑的副本  
>
> 可以运行 git merge origin/serverfix 将这些工作合并到当前所在的分支  
>
> $ git checkout -b <branch> <remote>/<branch>  

#### **跟踪分支**

从一个远程跟踪分支检出一个本地分支会自动创建所谓的“跟踪分支”（它跟踪的分支叫做“上游分支”）。跟踪分支是与远程分支有直接关系的本地分支。  

当克隆一个仓库时，它通常会自动地创建一个跟踪 origin/master 的 master 分支  

Git 提供了 --track 快捷方式  

```shell
$ git checkout --track <remote>/<branch>  
```

切换分支时，如果该分支不存在，刚好只有一个名字与支匹配的远程分支，那么Git会为你创建一个跟踪分支

如果想要将本地分支与远程分支设置为不同的名字，你可以轻松地使用上一个命令增加一个不同名字的本地分支：

```shell
git checkout -b <branch> <remote>/<branch>  
```

本地分支<branch> 会自动从<remote>/<branch>  拉取  

 设置已有的本地分支跟踪一个刚刚拉取下来的远程分支，或者想要修改正在跟踪的上游分支， 你可以在任意时间使用 -u 或 --set-upstream-to 选项运行 git branch 来显式地设置。  

```SHELL
$ git branch -u <remote>/<branch>  
```

> 上游快捷方式
>
> 当设置好跟踪分支后，可以通过简写 @{upstream} 或 @{u} 来引用它的上游分支。 所以在master 分支时并且它正在跟踪 origin/master 时，如果愿意的话可以使用 git merge @{u} 来取代 git merge origin/master  

如果想要查看设置的所有跟踪分支，可以使用 git branch 的 -vv 选项。 这会将所有的本地分支列出来并且包含更多的信息，如每一个分支正在跟踪哪个远程分支与本地分支是否是领先、落后或是都有。  

```shell
$ git branch -vv
```

需要重点注意的一点是这些数字的值来自于你从每个服务器上最后一次抓取的数据。 这个命令并没有连接服务器，它只会告诉你关于本地缓存的服务器数据。 如果想要统计最新的领先与落后数字，需要在运行此命令前抓取所有的远程仓库。 可以像这样做：  

```shell
$ git fetch --all; git branch -vv
```

#### **拉取**

当 git fetch 命令从服务器上抓取本地没有的数据时，它并不会修改工作目录中的内容。 它只会获取数据然后让你自己合并。  

git pull 在大多数情况下它的含义是一个 git fetch 紧接着一个git merge 命令 ，git pull 都会查找当前分支所跟踪的服务器与分支， 从服务器上抓取数据然后尝试合并入那个远程分支  

由于 git pull 的魔法经常令人困惑所以通常单独显式地使用 fetch 与 merge 命令会更好一些。  

#### **删除远程分支**

```shell
$ git push origin --delete <branch>
```

基本上这个命令做的只是从服务器上移除这个指针。 Git 服务器通常会保留数据一段时间直到垃圾回收运行，所以如果不小心删除掉了，通常是很容易恢复的。  

### 变基

在 Git 中整合来自不同分支的修改主要有两种方法：merge 以及 rebase 

![分叉的提交历史。](https://git-scm.com/book/en/v2/images/basic-rebase-1.png)



![通过合并操作来整合分叉了的历史。](https://git-scm.com/book/en/v2/images/basic-rebase-2.png)



![将 `C4` 中的修改变基到 `C3` 上。](https://git-scm.com/book/en/v2/images/basic-rebase-3.png)

```shell
$ git checkout experiment
$ git rebase master
```

```shell
$ git checkout master
$ git merge experiment
```

![`master` 分支的快进合并。](https://git-scm.com/book/en/v2/images/basic-rebase-4.png)

假设你希望将 `client` 中的修改合并到主分支并发布，但暂时并不想合并 `server` 中的修改， 因为它们还需要经过更全面的测试。这时，你就可以使用 `git rebase` 命令的 `--onto` 选项， 选中在 `client` 分支里但不在 `server` 分支里的修改（即 `C8` 和 `C9`），将它们在 `master` 分支上重放：

![从一个主题分支里再分出一个主题分支的提交历史。](https://git-scm.com/book/en/v2/images/interesting-rebase-1.png)

```shell
$ git rebase --onto master server client
```

![截取主题分支上的另一个主题分支，然后变基到其他分支。](https://git-scm.com/book/en/v2/images/interesting-rebase-2.png)

```shell
$ git checkout master
$ git merge client
```

![快进合并 `master` 分支，使之包含来自 `client` 分支的修改。](https://git-scm.com/book/en/v2/images/interesting-rebase-3.png)

```console
$ git rebase master server
```

![将 `server` 中的修改变基到 `master` 上。](https://git-scm.com/book/en/v2/images/interesting-rebase-4.png)

```shell
$ git checkout master
$ git merge server

$ git branch -d client
$ git branch -d server
```

![最终的提交历史。](https://git-scm.com/book/en/v2/images/interesting-rebase-5.png)

变基的风险：

呃，奇妙的变基也并非完美无缺，要用它得遵守一条准则：

**如果提交存在于你的仓库之外，而别人可能基于这些提交进行开发，那么不要执行变基。**

```
git pull --rebase

git fetch
git rebase origin/master
----- 解决冲突
git add 冲突文件

git rebase --continue
```

如果你只对不会离开你电脑的提交执行变基，那就不会有事。 如果你对已经推送过的提交执行变基，但别人没有基于它的提交，那么也不会有事。 如果你对已经推送至共用仓库的提交上执行变基命令，并因此丢失了一些别人的开发所基于的提交， 那你就有大麻烦了，你的同事也会因此鄙视你。

如果你或你的同事在某些情形下决意要这么做，请一定要通知每个人执行 `git pull --rebase` 命令，这样尽管不能避免伤痛，但能有所缓解。

### 变基 vs. 合并

至此，你已在实战中学习了变基和合并的用法，你一定会想问，到底哪种方式更好。 在回答这个问题之前，让我们退后一步，想讨论一下提交历史到底意味着什么。

有一种观点认为，仓库的提交历史即是 **记录实际发生过什么**。 它是针对历史的文档，本身就有价值，不能乱改。 从这个角度看来，改变提交历史是一种亵渎，你使用 *谎言* 掩盖了实际发生过的事情。 如果由合并产生的提交历史是一团糟怎么办？ 既然事实就是如此，那么这些痕迹就应该被保留下来，让后人能够查阅。

另一种观点则正好相反，他们认为提交历史是 **项目过程中发生的事**。 没人会出版一本书的第一版草稿，软件维护手册也是需要反复修订才能方便使用。 持这一观点的人会使用 `rebase` 及 `filter-branch` 等工具来编写故事，怎么方便后来的读者就怎么写。

现在，让我们回到之前的问题上来，到底合并还是变基好？希望你能明白，这并没有一个简单的答案。 Git 是一个非常强大的工具，它允许你对提交历史做许多事情，但每个团队、每个项目对此的需求并不相同。 既然你已经分别学习了两者的用法，相信你能够根据实际情况作出明智的选择。

总的原则是，只对尚未推送或分享给别人的本地修改执行变基操作清理历史， 从不对已推送至别处的提交执行变基操作，这样，你才能享受到两种方式带来的便利