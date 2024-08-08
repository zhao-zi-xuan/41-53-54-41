# 暑期培训第一讲

## 1.VS Code

### 拓展

Chinese (simplified)...

markdown all in one

markdown preview github styling

markdown preview mermaid support

markdownlint

github actions

## 2.git和github

### git

#### 1.简介

分布式版本控制
![版本控制](/版本控制.jpg)

#### 2.git 安装

> https://git-scm.com/downloads

#### 3.配置

```
git config --global user.name "your name"
git config --global user.email "yours@mails.com"
```

#### 4.工作原理

![]
#### 5.常见命令

```
git init
git add 具体文件名/-all
git commit -m “提交信息”/直接提交，进入备注页面（i+内容+esc+：wq）
git commit -am（一步提交）
git status 提交状态
git diff 文件名
git checkout 放弃修改
git log 查看提交日志
git reset --hard HEAD^/--hard HEAD~50
```

### github

#### 0.注册github账号

#### 1.github

- ssh配置
- 通过本地文件创建远程仓库
    ```git remote add origin +http```

   ```git push -u```

- 远程克隆到本地
    ```git clone +http```
- 更新
    ```git pull```
- 分支
    ```
    git branch
    git checkout -b/-d+newbranch
    git merge +branch
    ```

#### 2.github 页面讲解

## 3.markdown和mermaid

### 标题

```
# 一级标题

## 二级标题

### 三级标题

```

### 文本

粗体：**粗体**/ __粗体__

斜体：*斜体*/_斜体_

粗体+斜体：***粗体+斜体***/___粗体+斜体___

删除文本：~~删除~~

下划线：<u>下划线</u>

高亮：<mark>高亮</mark>

### 列表

#### 有序列表

数字+点+空格

1. 第一
2. 第二
3. 第三

#### 无序列表

-/*/+ + 空格

- 1
- 2
  + 2.1
  + 2.2
    * 3.1
    * 3.2

### 表格

以｜分割
姓名|学号|分数
-|-|-
孙悟空|2021|95
猪八戒|20211|96

### 代码

代码块：首行缩进一个制表符/首尾用```包围

    printf("%d",a);

代码块高亮：首尾用```包围并加上语言标识

```C
int a;
```

### 链接与图像

链接：[链接标题]（链接）

this is a picture[picture](https://i2.hdslb.com/bfs/archive/7cb3fa5b5caf5622395176dd10d9ee8b64757284.jpg)

图像：![图像文字]（链接）

this is a picture ![picture](/picture.png)

### 数学公式

公式首尾+$

```
$a^2+b^2=c^2$

$\sqrt{2}$
```

$a^2+b^2=c^2$

$\sqrt{2}$

### 流程图?(只需要讲流程图，剩下的给他们看一下)

```graph TD;
A --> b;
b --> c[judge];

