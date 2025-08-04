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