static size_t djb_hash(const char* cp)
{
	size_t hash = 5381;
	while (*cp)
		hash = 33 * hash ^ (unsigned char) *cp++;
	return hash;
}

/* Fowler/Noll/Vo (FNV) hash function, variant 1a */
static size_t fnv1a_hash(const char* cp)
{
	size_t hash = 0x811c9dc5;
	while (*cp) {
		hash ^= (unsigned char) *cp++;
		hash *= 0x01000193;
	}
	return hash;
}