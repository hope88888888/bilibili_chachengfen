#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define ran domcolor

#ifndef randomcolor
int color[] = {
0XFF0000, 0XFF4500, 0XFF1493, 0XFF00FF, 0XA52A2A,
0XDC143C, 0XD2691E,
0XFFA500, 0XFFC0CB, 0XBA55D3, 0XEE82EE,
0XFFD700, 0X00008B, 0X0000FF, 0X8470FF, 0X4169E1,
0X6495ED, 0X8A2BE2, 0X00CED1, 0X48D1CC,
0X00BFFF, 0X87CEFA, 0X008000,
0X32CD32
};
#endif

#ifdef randomcolor
int RandomColor() {
#define rgb (rand()%256)
    return (((rgb << 8) + rgb) << 8) + rgb;
}
#endif

int main() {
#ifdef randomcolor
    srand(time(0));
#endif
#ifndef randomcolor
    int max_color = sizeof(color) / 4;
#endif
    FILE* fp;
    if ((fp = fopen("__in.txt", "r")) == NULL) {
        printf("open __in.txt warning\n");
        getchar();
        exit(0);
    }
    freopen("bilibili_wen_wen_need_v.user.js", "w", stdout);
    printf("// ==UserScript==\n\
// @name         bilibili_when_when_need_v\n\
// @namespace    https://github.com/hope88888888/bilibili_chachengfen\n\
// @version      1.0\n\
// @description  bilibili can can need\n\
// @author       hope88888888\n\
// @match        https://www.bilibili.com/video/*\n\
// @match        https://t.bilibili.com/*\n\
// @match        https://space.bilibili.com/*\n\
// @match        https://space.bilibili.com/*\n\
// @match        https://www.bilibili.com/read/*\n\
// @icon         https://static.hdslb.com/images/favicon.ico\n\
// @connect      bilibili.com\n\
// @grant        GM_xmlhttpRequest\n\
// @license MIT\n\
// @run-at document-end\n\
// ==/UserScript==\n");
    printf("(function () {\n");
    char str[1000] = { 0 }, key[100], tag[100];
    int i = 0;
    srand(time(0));
    while (fgets(str, 1000, fp)) {
        sscanf(str, "%s %s", key, tag);
        printf("\
	const num%d = new Set()\n\
	const no_num%d = new Set()\n\
	const key_num%d = \"%s\"\n\
	const tag_num%d = \"%s\"\n\
	const tag_num%d_Inner = \"<b style='color: #%06X'> \" + tag_num%d + \" </b>\"\n\
"
#ifndef randomcolor
, i, i, i, key, i, tag, i, color[rand() % max_color], i);
#endif
#ifdef randomcolor
, i, i, i, key, i, tag, i, RandomColor(), i);
#endif
        i++;
    }
    printf("    const blog = 'https://api.bilibili.com/x/polymer/web-dynamic/v1/feed/space?&host_mid='\n\
const is_new = document.getElementsByClassName('item goback').length != 0\n\
const get_pid = (c) => {\n\
        if (is_new) {\n\
            return c.dataset['userId']\n\
        } else {\n\
            return c.children[0]['href'].replace(/[^\d]/g, "")\n\
        }\n\
    }\n\
     const get_comment_list = () => {\n\
        if (is_new) {\n\
            let lst = new Set()\n\
                for (let c of document.getElementsByClassName('user-name')) {\n\
                    lst.add(c)\n\
                }\n\
            for (let c of document.getElementsByClassName('sub-user-name')) {\n\
                lst.add(c)\n\
            }\n\
            return lst\n\
        }\n\
        else {\n\
            return document.getElementsByClassName('user')\n\
        }\n\
    }\n\
console.log(\"success\")\n\
let jiance = setInterval(() => {\n\
let commentlist = get_comment_list()\n\
if (commentlist.length != 0) {\n\
    commentlist.forEach(c => {\n\
        let pid = get_pid(c)\n");
    rewind(fp); i = 0;
    while (fgets(str, 100, fp)) {
        printf("\n\
                    if (num%d.has(pid)) {\n\
                    if (c.textContent.includes(tag_num%d) === false) {\n\
                        c.innerHTML += tag_num%d_Inner\n\
                    }\n\
                    return\n\
                } else if (no_num%d.has(pid)) {\n\
                    return\n\
                }", i, i, i, i);
        i++;
    }
    printf("\n\
                let blogurl = blog + pid\n\
                GM_xmlhttpRequest({\n\
                    method: \"get\",\n\
                    url: blogurl,\n\
                    data: '',\n\
                    headers: {\n\
                        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.0.0 Safari/537.36'\n\
                    },\n\
                    onload: function (res) {\n\
                        if (res.status === 200) {\n\
                            let st = JSON.stringify(JSON.parse(res.response).data)\n");
    rewind(fp); i = 0;
    int temp;
#ifndef randomcolor
    printf("var t = 0\nc.innerHTML += \"<b style='color: #%06X' >[</b>\"\n", temp = color[rand() % max_color]);
#endif
#ifdef randomcolor
    printf("var t = 0\nc.innerHTML += \"<b style='color: #%06X' >[</b>\"\n", temp = RandomColor());
#endif 
    while (fgets(str, 100, fp)) {
        sscanf(str, "%s %s", key, tag);
        printf("\n\
                //input %s\n\
                if (st.includes(key_num%d)) {\n\
                    c.innerHTML += tag_num%d_Inner\n\
                        num%d.add(pid)\n\
                        t++\n\
                }\n\
                else {\n\
                    no_num%d.add(pid)\n\
                }\n", key, i, i, i, i);
        i++;
    }
    printf("if(!t) c.innerHTML += \"good b\"\n\
        c.innerHTML += \"<b style='color: #%06X' >]</b>\"\n", temp);
    printf("}\n\
                    },\n\
                });\n\
            });\n\
        }\n\
    }, 4000)\n\
})();");
    fclose(fp);
    fclose(stdout);
    return 0;
}