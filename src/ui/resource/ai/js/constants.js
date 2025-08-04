const UserContainerIdPrefix = 'msg-user-';
const ResponseContainerIdPrefix = 'msg-response-';

const ChatMessageState = {
    currentChatId: null,    // 当前聊天的id
    currentGroupId: null,   // 当前组，可以为空

    lastMsgId: null,        // 最新一条发送信息的id
    lastResponseContainer: null,    // 最后一个接收容器

    waitingMsg: false,      // 正在等待消息
    receivingMsg: false,    // 正在接收消息
}

const UploadFileState = {
    uploadedFiles: [],          // 已上传的文件
    uploadingFiles: new Map(),  // 上传中的文件
}

const TimerState = {
    timer: null,
    running: false,
}

const Response=
    "### 您好！我注意到您提到使用C++实现冒泡排序算法。但作为参考，我可以为您提供一个标准的C++冒泡排序实现代码：\n" +
    "```cpp\n" +
    "// MarkdownHighlighter.h\n" +
    "#pragma once\n" +
    "#include <QSyntaxHighlighter>\n" +
    "#include <QTextDocument>\n" +
    "#include <QRegularExpression>\n\n" +
    "class MarkdownHighlighter : public QSyntaxHighlighter {\n" +
    "    Q_OBJECT\n" +
    "public:\n" +
    "    explicit MarkdownHighlighter(QTextDocument *parent = nullptr);\n" +
    "    void setRawMarkdown(const QString &markdown); // 存储原始文本\n\n" +
    "protected:\n" +
    "    void highlightBlock(const QString &text) override;\n\n" +
    "private:\n" +
    "    QString m_rawMarkdown;\n" +
    "    QVector<QPair<int, int>> m_codeBlocks; // 代码块起始/结束位置\n" +
    "\n" +
    "    void detectCodeBlocks();\n" +
    "};" +
    "```\n\n" +
    "| 文件扩展名 | 图标类型       | 适用文件格式             |\n" +
    "|------------|----------------|--------------------------|\n" +
    "| .pdf     | PDF 文档       | Adobe PDF 文件           |\n" +
    "| .doc     | Word 文档      | Microsoft Word (旧格式)   |\n" +
    "| .docx    | Word 文档      | Microsoft Word (新格式)   |\n" +
    "| .xls     | Excel 表格     | Microsoft Excel (旧格式)  |\n" +
    "| .xlsx    | Excel 表格     | Microsoft Excel (新格式)  |\n" +
    "| .ppt     | PPT 演示文稿   | Microsoft PowerPoint (旧格式) |\n" +
    "| .pptx    | PPT 演示文稿   | Microsoft PowerPoint (新格式) |\n" +
    "| .txt     | 纯文本文件     | 无格式文本文件            |\n" +
    "| .jpg     | 图片文件       | JPEG 图像                |\n" +
    "| .png     | 图片文件       | PNG 图像                 |\n" +
    "| .gif     | 动态图片       | GIF 图像                 |\n" +
    "| .mp3     | 音频文件       | MP3 音乐                 |\n" +
    "| .mp4     | 视频文件       | MP4 视频                 |\n" +
    "| .zip     | 压缩文件       | ZIP 压缩包               |\n" +
    "| .rar     | 压缩文件       | RAR 压缩包               |\n" +
    "| 其他       | 默认文件图标   | 未列出的文件类型          |\n\n" +
    "如果您需要DMSAS软件中关于数据分析的帮助，比如排序数据或进行统计分析，我很乐意为您提供DMSAS的操作指导。\n\n" +
    "```python\n" +
    "def main()\n" +
    "```\n"