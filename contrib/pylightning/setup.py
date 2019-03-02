from setuptools import setup

with open('README.md', encoding='utf-8') as f:
    long_description = f.read()

setup(name='pylightning',
      version='0.0.6',
      description='Client library for lightningd',
      long_description=long_description,
      long_description_content_type='text/markdown',
      url='http://github.com/Groestlcoin/lightning',
      author='Groestlcoin Developers',
      author_email='groestlcoin@gmail.com',
      license='MIT',
      packages=['lightning'],
      scripts=['lightning-pay'],
      zip_safe=True)
