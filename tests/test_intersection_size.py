""""""
from geneweaver.tools.mset.cpp import mset
import pytest

@pytest.mark.parametrize(
    "a, b, expected",
    [
        ([1, 2, 3], [2, 3, 4], 2),
        ([1, 2, 3], [4, 5, 6], 0),
        ([1, 2, 3], [1, 2, 3], 3),
        ([1, 2, 3], [3, 2, 1], 3),
        ([1, 2, 3], [1, 2, 2], 2),
        ([1, 2, 3], [1, 1, 1], 1),
        ([1, 2, 3], [1, 1, 1, 2, 2, 2, 3, 3, 3], 3),
        ([1, 1, 1, 2, 2, 2, 3, 3, 3], [1, 2, 3], 3),
    ]
)
def test_intersection_size(a, b, expected):
    result = mset.intersection_size(a, b)
    assert result == expected