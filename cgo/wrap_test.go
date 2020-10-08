package clustering

import (
	"fmt"
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
	fmt.Printf(
		"Got %d clusters, %s: %d, %s: %d, %s: %d\n", n,
		elems[0].Label, elems[0].Cluster,
		elems[1].Label, elems[1].Cluster,
		elems[2].Label, elems[2].Cluster,
	)
}
