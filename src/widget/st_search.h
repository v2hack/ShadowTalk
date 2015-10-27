#ifndef ST_SEARCH_H
#define ST_SEARCH_H


class Search
{
public:
    /* 匹配并显示搜索结果 */
    static void matchAndShowSearchResult();

    /* 检测搜寻输入框的内容是否为空 */
    static int checkSearchText();

    /* 设置搜寻结果框不可见 */
    static void setSearchTextUnvisible();

    /* 清理search listview中的内容 */
    static void clearSearchWidget();
};


#endif // ST_SEARCH_H

