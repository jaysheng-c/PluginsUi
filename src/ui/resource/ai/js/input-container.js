function initInputContainer() {
    const userInput = document.getElementById('user-input');
    const sendBtn = document.getElementById('send-btn');
    const stopBtn = document.getElementById('stop-btn');

    userInput.addEventListener('keypress', function(e){
        if (e.key === 'Enter' && !e.shiftKey) {
            e.preventDefault();
            if (sendBtn) {
                sendBtn.click();
            }
        }
    });
    userInput.addEventListener('input', adjustInputHeight);
    sendBtn.addEventListener('click', sendMsg);
    stopBtn.addEventListener('click', stopMsg);

    setSendState(false);
}

// 滚动条到最底部
function scrollToBottom(element) {
    requestAnimationFrame(() => {
        element.scrollTop = element.scrollHeight;
    });
}

function setSendState(sending) {
    const sendBtn = document.getElementById('send-btn');
    const stopBtn = document.getElementById('stop-btn');
    sendBtn.style.display = sending ? 'none' : 'block';
    stopBtn.style.display = !sending ? 'none' : 'block';
}

function adjustInputHeight() {
    const input = document.getElementById('user-input');
    input.style.height = 'auto';
    const newHeight = Math.min(input.scrollHeight, 120);
    input.style.height = newHeight + 'px';

    // 根据是否需要滚动条来添加/移除类
    if (input.scrollHeight > newHeight) {
        input.classList.add('scrollable');
    } else {
        input.classList.remove('scrollable');
    }
}

function checkState() {
    if (ChatMessageState.waitingMsg || ChatMessageState.receivingMsg) {
        window.alert('请先停止对话！');
        return false;
    }
    if (UploadFileState.uploadingFiles.size > 0) {
        window.alert('请等待文件上传完成！');
        return false;
    }
    return true;
}

// 处理用户信息
function processUserMessage(text) {
    if (!text || text === '') {
        return false;
    }
    const container = document.getElementById('chat-container');
    const msgContainer = document.createElement('div');
    msgContainer.className = 'message-container user';
    msgContainer.id = UserContainerIdPrefix + ChatMessageState.lastMsgId;

    const ctxtDiv = document.createElement('div');
    ctxtDiv.className = 'message-content';

    // 是否存在文件上传
    if (UploadFileState.uploadedFiles.length > 0) {
        // 存在上传的文件，添加文件预览
        const fileContainer = document.getElementById('file-upload-container');
        if (fileContainer) {
            const  previewContainer = document.createElement('div');
            previewContainer.className = 'files-preview-container';
            previewContainer.innerHTML = fileContainer.innerHTML;
            ctxtDiv.appendChild(previewContainer);
        }
    }
    // 消息
    const msgDiv = document.createElement('div');
    msgDiv.className = 'message user-message';
    msgDiv.textContent = text;
    ctxtDiv.appendChild(msgDiv);

    msgContainer.appendChild(ctxtDiv);
    container.appendChild(msgContainer);

    scrollToBottom(container);
    return true;
}

function fileUploadBtn(event) {
    event.stopPropagation();
    const uploadMenu = document.getElementById('upload-menu');
    const isShowing = uploadMenu.classList.contains('show');

    clearMenu();

    // 隐藏所有其他菜单
    document.querySelectorAll('.upload-menu').forEach(menu => {
        if (menu !== uploadMenu) menu.classList.remove('show');
    });

    uploadMenu.classList.toggle('show', !isShowing);
}

function sendMsg() {
    const userInput = document.getElementById('user-input');
    const message = userInput.value.trim();
    if (!checkState()) {
        return;
    }
    if (message) {
        console.log("sendMsg", message);

        setWelcomeState(false);
        const oldId = ChatMessageState.lastMsgId;
        ChatMessageState.lastMsgId = Date.now();
        if (!processUserMessage(message)) {
            ChatMessageState.lastMsgId = oldId;
            window.alert('信息发送失败！');
            return;
        }
        // TODO: 发送消息到后台，并且启动接收

        userInput.value = '';
        setSendState(true);
    }
}

function stopMsg() {
    setSendState(false);

    // TODO: 暂替消息接受
}



