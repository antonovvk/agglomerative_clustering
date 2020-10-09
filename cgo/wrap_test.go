package clustering

import (
	"testing"
)

func TestBasic(t *testing.T) {
	elems := []*Element{
		{
			Label: "foo",
			Sims: map[string]float32{
				"bar": 0.1,
				"wat": 0.9,
			},
		},
		{
			Label: "bar",
			Sims: map[string]float32{
				"foo": 0.1,
			},
		},
		{
			Label: "wat",
			Sims: map[string]float32{
				"foo": 0.9,
			},
		},
	}
	n, err := AgglomerativeClustering(elems, DefaultParameters())
	if n == -1 {
		t.Error(err)
	}
	if n != 2 || elems[0].Cluster != 0 || elems[1].Cluster != 1 || elems[2].Cluster != 0 {
		t.Errorf("Got %d clusters: %v\n", n, elems)
	}
}
