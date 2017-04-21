from distutils.core import setup, Extension

gst_gost_module = Extension('gst_gost',
                               sources = ['gostmodule.c',
                                          'gost.c'],
                               include_dirs=['.'])

setup (name = 'gst_gost',
       version = '1.0',
       description = 'Bindings for GOST proof of work used by Gostcoin',
       ext_modules = [gst_gost_module])
