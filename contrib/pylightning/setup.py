from setuptools import setup
import lightning
import io


with io.open('README.md', encoding='utf-8') as f:
    long_description = f.read()

with io.open('requirements.txt', encoding='utf-8') as f:
    requirements = [r for r in f.read().split('\n') if len(r)]

setup(name='pylightning',
      version=lightning.__version__,
      description='Client library for lightningd',
      long_description=long_description,
      long_description_content_type='text/markdown',
      url='http://github.com/Groestlcoin/lightning',
      author='Groestlcoin Developers',
      author_email='groestlcoin@gmail.com',
      license='MIT',
      packages=['lightning'],
      zip_safe=True,
      install_requires=requirements)
