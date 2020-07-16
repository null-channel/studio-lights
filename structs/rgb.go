package structs

type Status struct {
	On bool
}

type Lights struct {
	Status Status
	Red int
	Blue int
	Green int
}
