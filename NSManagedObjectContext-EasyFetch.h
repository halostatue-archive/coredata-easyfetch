/** Core Data Easy Fetch Category
 *
 * This is an Objective-C category for Core Data (`NSManagedObjectContext
 * (EasyFetch)`) that offers a few useful functions added that simplify [Core
 * Data][1] programming for Mac OS X and iPhone OS. It's based loosely on
 * [code][2] by Matt Gallagher, but with several enhancements and modifications
 * that I needed for a project I was writing that used Core Data.
 *
 * 1: http://developer.apple.com/mac/library/DOCUMENTATION/Cocoa/Conceptual/CoreData/index.html
 * 2: http://cocoawithlove.com/2008/03/core-data-one-line-fetch.html
 */
/** Copyright &copy; 2009, 2010 Austin Ziegler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

@interface NSManagedObjectContext (EasyFetch)
#pragma mark -
#pragma mark Fetch all unsorted

/** @brief Convenience method to fetch all objects for a given Entity name in
 * this context.
 *
 * The objects are returned in the order specified by Core Data.
 */
- (NSArray*)fetchObjectsForEntityName:(NSString*)entityName;

#pragma mark -
#pragma mark Fetch all sorted

/** @brief Convenience method to fetch all objects for a given Entity name in
 * the context.
 *
 * The objects are returned in the order specified by the provided key and
 * order.
 */
- (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                            sortByKey:(NSString*)key
                            ascending:(BOOL)ascending;

/** @brief Convenience method to fetch all objects for a given Entity name in
 * the context.
 *
 * If the sort descriptors array is not nil, the objects are returned in the
 * order specified by the sort descriptors. Otherwise, the objects are returned
 * in the order specified by Core Data.
 */
- (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                             sortWith:(NSArray*)sortDescriptors;

#pragma mark -
#pragma mark Fetch filtered unsorted

/** @brief Convenience method to fetch selected objects for a given Entity name
 * in the context.
 *
 * If the predicate is not nil, the selection is filtered by the provided
 * predicate.
 *
 * The objects are returned in the order specified by Core Data.
 */
- (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                        withPredicate:(NSPredicate*)predicate;

/** @brief Convenience method to fetch selected objects for a given Entity name
 * in the context.
 *
 * The selection is filtered by the provided formatted predicate string and
 * arguments.
 *
 * The objects are returned in the order specified by Core Data.
 */
- (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                  predicateWithFormat:(NSString*)predicateFormat, ...;

#pragma mark -
#pragma mark Fetch filtered sorted

/** @brief Convenience method to fetch selected objects for a given Entity name
 * in the context.
 *
 * If the predicate is not nil, the selection is filtered by the provided
 * predicate.
 *
 * The objects are returned in the order specified by the provided key and
 * order.
 */
- (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                            sortByKey:(NSString*)key
                            ascending:(BOOL)ascending
                        withPredicate:(NSPredicate*)predicate;

/** @brief Convenience method to fetch selected objects for a given Entity name
 * in the context.
 *
 * If the predicate is not nil, the selection is filtered by the provided
 * predicate.
 */
- (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                            sortWith:(NSArray*)sortDescriptors
                        withPredicate:(NSPredicate*)predicate;

/** @brief Convenience method to fetch selected objects for a given Entity name
 * in the context.
 *
 * The selection is filtered by the provided formatted predicate string and
 * arguments.
 *
 * The objects are returned in the order specified by the provided key and
 * order.
 */
- (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                            sortByKey:(NSString*)key
                            ascending:(BOOL)ascending
                  predicateWithFormat:(NSString*)predicateFormat, ...;

/** @brief Convenience method to fetch selected objects for a given Entity name
 * in the context.
 *
 * The selection is filtered by the provided formatted predicate string and
 * arguments.
 *
 * If the sort descriptors array is not nil, the objects are returned in the
 * order specified by the sort descriptors. Otherwise, the objects are returned
 * in the order specified by Core Data.
 */
- (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                             sortWith:(NSArray*)sortDescriptors
                  predicateWithFormat:(NSString*)predicateFormat, ...;
@end
