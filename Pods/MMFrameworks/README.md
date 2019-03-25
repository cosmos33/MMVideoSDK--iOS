底层framework拆分
拆分目录如下:
    1.MMFoundation 对Foundation的扩展
      ...
      ......
  
管理方式:
    在workspace下管理多个framework，最终build到统一framework存放目录，并以自定义的pod依赖引用。