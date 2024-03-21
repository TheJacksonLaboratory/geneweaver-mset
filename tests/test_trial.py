""""""

import pytest
import statistics
from geneweaver.tools.mset.cpp import mset


@pytest.mark.parametrize(
    ("l1", "l2", "universe", "expected_min", "expected_max"),
    [
        ([1, 2, 3], [2, 3, 4], 4, 2, 3),
        ([1, 2, 3], [4, 5, 6], 6, 1, 2),
        ([1, 2, 3], [1, 2, 3], 3, 3, 3),
        ([1, 2, 3], [3, 2, 1], 3, 3, 3),
        ([1, 2, 3], [1, 2, 2], 3, 2, 4),
        ([1, 2, 3], [1, 1, 1], 3, 2, 4),
        ([1, 2, 3], [1, 1, 1, 2, 2, 2, 3, 3, 3], 3, 3, 3),
        ([1, 1, 1, 2, 2, 2, 3, 3, 3], [1, 2, 3], 3, 3, 3),
    ]
)
def test_trial(l1, l2, universe, expected_min, expected_max):
    result = statistics.fmean([mset.trial(l1, l2, universe) for _ in range(100000)])
    print(result)
    assert expected_min <= result <= expected_max
