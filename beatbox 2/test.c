static void fillPlaybackBuffer(short *playbackBuffer, int size)
{
	/*
	 * REVISIT: Implement this
	 * Notes on "adding" PCM samples:
	 * - PCM is stored as signed shorts (between SHRT_MIN and SHRT_MAX).
	 * - When adding values, ensure there is not an overflow. Any values which would
	 *   greater than SHRT_MAX should be clipped to SHRT_MAX; likewise for underflow.
	 * - Don't overflow any arrays!
	 * - Efficiency matters here! The compiler may do quite a bit for you, but it doesn't
	 *   hurt to keep it in mind. Here are some tips for efficiency and readability:
	 *   * If, for each pass of the loop which "adds" you need to change a value inside
	 *     a struct inside an array, it may be faster to first load the value into a local
	 *      variable, increment this variable as needed throughout the loop, and then write it
	 *     back into the struct inside the array after. For example:
	 *           int offset = myArray[someIdx].value;
	 *           for (int i =...; i < ...; i++) {
	 *               offset ++;
	 *           }
	 *           myArray[someIdx].value = offset;
	 *   * If you need a value in a number of places, try loading it into a local variable
	 *          int someNum = myArray[someIdx].value;
	 *          if (someNum < X || someNum > Y || someNum != Z) {
	 *              someNum = 42;
	 *          }
	 *          ... use someNum vs myArray[someIdx].value;
	 *
	 */


	// 1. Wipe the playbackBuffer to all 0's to clear any previous PCM data.
	//    Hint: use memset()
	memset(playbackBuffer, 0 , playbackBufferSize*sizeof(*playbackBuffer)); 

	// 2. Since this is called from a background thread, and soundBites[] array
	//    may be used by any other thread, must synchronize this.

	// 3. Loop through each slot in soundBites[], which are sounds that are either
	//    waiting to be played, or partially already played:
	//    - If the sound bite slot is unused, do nothing for this slot.
	//    - Otherwise "add" this sound bite's data to the play-back buffer
	//      (other sound bites needing to be played back will also add to the same data).
	//      * Record that this portion of the sound bite has been played back by incrementing
	//       the location inside the data where play-back currently is.
	//     * If you have now played back the entire sample, free the slot in the
	//        soundBites[] array.
	//printf("line 316 - audioMixer\n");
	for (int i = 0; i < MAX_SOUND_BITES; ++i){
		
		//int numSamples = soundBites[i].pSound->numSamples;
		//printf("line 320 - audioMixer\n");
		if( soundBites[i].pSound != NULL){ //if not empty

			int location = soundBites[i].location;
			int playBuffIndex = 0;
			int addedData = 0;
			//printf("line 326 - audioMixer\n");
			while( location < soundBites[i].pSound->numSamples && playBuffIndex < playbackBufferSize)
			{
				//printf("line 329 - audioMixer\n");
				//printf("\t\tlocation = %d\n", location); //location -1, segfaults here!
				int pData_location = (int) soundBites[i].pSound->pData[location];
				//printf("line 331 - audioMixer\n");
				addedData = ((int) playbackBuffer[playBuffIndex] + pData_location);
				//printf("line 333 - audioMixer\n");
				if(addedData > SHRT_MAX){
					addedData = SHRT_MAX;
				}

				if(addedData < SHRT_MIN){
					addedData = SHRT_MIN;
				}
				//printf("line 341 - audioMixer\n");
				playbackBuffer[playBuffIndex] = (short) addedData;
				//printf("line 343 - audioMixer\n");
				location++;
				playBuffIndex++;
			}
			
			soundBites[i].location = location;

			//printf("line 347 - audioMixer\n");
			//printf("i = %d\n", i);
			if(soundBites[i].location >= soundBites[i].pSound->numSamples){
				//printf("line 358 - audioMixer\n");
				//AudioMixer_freeWaveFileData(soundBites[i].pSound); //free data in pSound
				soundBites[i].pSound = NULL;
			}
			//printf("line 362 - audioMixer\n");
		}
		

	}
	//printf("line 364 - audioMixer\n");

}