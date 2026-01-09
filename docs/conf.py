import os, subprocess

project = 'result'
copyright = '2022-2026, Alfi Maulana'
author = 'Alfi Maulana'

extensions = ['breathe']

dir_path = os.path.dirname(os.path.realpath(__file__))
subprocess.call('cd %s && doxygen' % dir_path, shell=True)

breathe_projects = {"result": "_xml"}
breathe_default_project = "result"

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
