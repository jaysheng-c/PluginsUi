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
    userInput.focus();
}

// 滚动条到最底部
function scrollToBottom(element) {
    if (!element) {
        return;
    }
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

function createResponseContainer(initialText) {
    const container = document.getElementById('chat-container');
    const msgContainer = document.createElement('div');
    msgContainer.className = 'message-container';
    msgContainer.id = ResponseContainerIdPrefix + ChatMessageState.lastMsgId;

    // 消息容器
    const ctxDiv = document.createElement('div');
    ctxDiv.className = 'message-content';

    // 消息体
    const msgDiv = document.createElement('div');
    msgDiv.className = 'message assistant-message';
    msgDiv.textContent = initialText;

    // 消息体的按键区域
    const msgBtnContainer = document.createElement('div');
    msgBtnContainer.className = 'message-buttons';

    ctxDiv.appendChild(msgDiv);
    ctxDiv.appendChild(msgBtnContainer);
    msgContainer.appendChild(ctxDiv)
    container.appendChild(msgContainer);

    ChatMessageState.lastResponseContainer = msgContainer;
}

function processResponse(text) {
    if (!ChatMessageState.lastResponseContainer || (!ChatMessageState.waitingMsg && !ChatMessageState.receivingMsg)) {
        console.warn('processResponse failed');
        return;
    }
    ChatMessageState.waitingMsg = false;
    ChatMessageState.receivingMsg = true;

    const msgContainer = ChatMessageState.lastResponseContainer;
    const ctxDiv = msgContainer.querySelector('.message');
    if (!ctxDiv) {
        console.warn('processResponse can not find message', ctxDiv);
        return;
    }
    const html = marked.parse(text);
    const tmpDiv = document.createElement('div');
    tmpDiv.innerHTML = html;

    // 处理所有代码块
    processCodeBlocks(tmpDiv);
    // 处理表格等其他需要特殊样式的元素
    processTables(tmpDiv);
    // 将处理后的内容添加到消息区域
    ctxDiv.innerHTML = '';
    ctxDiv.appendChild(tmpDiv);
    scrollToBottom(document.getElementById('chat-container'));
}

function processCodeBlocks(container) {
    const codeBlocks = container.querySelectorAll('pre code');
    codeBlocks.forEach((codeBlock) => {
        const preElement = codeBlock.parentElement;
        const lang = getCodeLanguage(codeBlock);
        const code = codeBlock.textContent;
        const codeContainer = createCodeContainer(lang, code);
        preElement.parentNode.replaceChild(codeContainer, preElement);
        hljs.highlightElement(codeContainer.querySelector('code'));
    });
}
function getCodeLanguage(codeElement) {
    const classNames = codeElement.className.split(' ');
    for (const className of classNames) {
        if (className.startsWith('language-')) {
            return className.replace('language-', '') || 'text';
        }
    }
    return 'text';
}
// 创建代码容器
function createCodeContainer(lang, code) {
    const container = document.createElement('div');
    container.className = 'code-container';
    container.innerHTML = `
            <div class="code-header">
                <span class="code-language">${lang}</span>
                <div>
                    <button class="code-btn" onclick="copyCode(this)">
                        <img src="./image/copy.png" alt="代码复制">
                    </button>          
                    <span style="border-left: 1px solid #707070;height: 100%; margin-left: 2px; margin-right: 5px;"></span>
                    <button class="code-btn" onclick="copyCode(this)">
                        <img src="./image/expand_code.png" alt="代码展开">
                    </button>      
                </div>
            </div>
            <div class="code-content">
                <pre><code class="language-${lang}" style="background-color: #FFFFFF;">${escapeHtml(code)}</code></pre>
            </div>
        `;
    return container;
}

function copyCode(btn) {

}

function processTables(container) {
    const tables = container.querySelectorAll('table');
    tables.forEach(table => {
        // 添加基础表格类
        table.classList.add('markdown-table');

        // 创建表格容器用于响应式滚动
        const tableWrapper = document.createElement('div');
        tableWrapper.className = 'table-responsive';

        // 包裹原表格
        table.parentNode.insertBefore(tableWrapper, table);
        tableWrapper.appendChild(table);

        // 添加表头高亮
        const headers = table.querySelectorAll('th');
        headers.forEach(header => {
            header.classList.add('table-header');
        });

        // 添加斑马条纹
        const rows = table.querySelectorAll('tr');
        rows.forEach((row, index) => {
            if (index % 2 === 1) {
                row.classList.add('striped-row');
            }
        });

        // 添加悬停效果
        table.addEventListener('mouseover', (e) => {
            if (e.target.tagName === 'TD') {
                const row = e.target.parentElement;
                row.classList.add('hover-row');
            }
        });

        table.addEventListener('mouseout', (e) => {
            if (e.target.tagName === 'TD') {
                const row = e.target.parentElement;
                row.classList.remove('hover-row');
            }
        });
    });
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
        ChatMessageState.waitingMsg = true;
        createResponseContainer('1111111');
        // TODO: 发送消息到后台，并且启动接收
        processResponse(Response);

        userInput.value = '';
        setSendState(true);
    }
}

function stopMsg() {
    setSendState(false);

    // TODO: 暂替消息接受
}



