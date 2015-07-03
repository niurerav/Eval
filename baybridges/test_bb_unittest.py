import unittest
from ctypes import *

class TestBB(unittest.TestCase):

	def setUp(self):
		pass

	def test_array_get_max_postion(self):
		self.assertEqual(max_position([1, 2, 3, 6, 4, 3, 4]), 3)

if __name__ == '__main__':
	unittest.main()