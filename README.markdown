# Core Data Easy Fetch Category

This is an Objective-C category for Core Data (`NSManagedObjectContext
(EasyFetch)`) that offers a few useful functions added that simplify [Core
Data][1] programming for Mac OS X and iPhone OS. It's based loosely on
[code][2] by Matt Gallagher, but with several enhancements and modifications
that I needed for a project I was writing that used Core Data.

## License

This category is released under the MIT license.

> Copyright &copy; 2009, 2010 Austin Ziegler

> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:

> The above copyright notice and this permission notice shall be included in
> all copies or substantial portions of the Software.

> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE.

## Using `NSManagedObjectContext (EasyFetch)`

1. Add the files to your Xcode project:

        NSManagedObjectContext-EasyFetch.h
        NSManagedObjectContext-EasyFetch.m

2. Import the header in an implementation file that uses Core Data where you
   need the functionality:

         #import "NSManagedObjectContext-EasyFetch.h"

3. Call one of the category methods:

        [[self managedObjectContext] fetchObjectsForEntityName:@"Employee"
                                           predicateWithFormat:@"(lastName LIKE[c] 'Worsley') AND (salary > %@)",
                                                               minimumSalary];

## Methods in `NSManagedObjectContext (EasyFetch)`

There are several methods added in the `EasyFetch` category, but they're all
variations on two basic options for a query, which simplifies understanding
them.

1. Should the objects returned be filtered?
2. Should the objects returned be sorted?

Accordingly, there are four categories of methods:

1. All objects, unsorted
2. All objects, sorted
3. Some objects, unsorted
4. Some objects, sorted

All methods return an `NSArray` of objects returned by the query. Any
exceptions thrown are unhandled by the category.

### All objects, unsorted

    - (NSArray*)fetchObjectsForEntityName:(NSString*)entityName;

Returns all objects from an entity in Core Data's natural (unsorted) order. Use
only when you don't care about the order in which objects are processed.

### All objects, sorted

    - (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                                 sortWith:(NSArray*)sortDescriptors;

Returns all objects from an entity, sorted by the `NSArray` containing
`NSSortDescriptor` objects.

    - (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                                sortByKey:(NSString*)key
                                ascending:(BOOL)ascending;

Returns all objects from an entity, sorted by the key value (which must be an
attribute in the entity). Creates an `NSSortDescriptor` object based on the
`key` and `ascending` values.

### Some objects, unsorted

    - (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                            withPredicate:(NSPredicate*)predicate;

Returns the objects in an entity that match the predicate comparison rules in
natural order. Use this version and construct your `NSPredicate` value
appropriately for predicate parameters that contain user input.

    - (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                      predicateWithFormat:(NSString*)predicateFormat, ...;

Returns the objects in an entity that match the constructed predicate, in
natural order. An `NSPredicate` will be created using `[NSPredicate
predicateWithFormat:arguments:]`. Fast and easy, but unsafe for values that
involve user input.

### Some objects, sorted

    - (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                                 sortWith:(NSArray*)sortDescriptors
                            withPredicate:(NSPredicate*)predicate;

Returns the objects in an entity that match the predicate comparison rules,
sorted by the `NSArray` containing `NSSortDescriptor` objects. Use this version
and construct your `NSPredicate` value appropriately for predicate parameters
that contain user input.

    - (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                                sortByKey:(NSString*)key
                                ascending:(BOOL)ascending
                            withPredicate:(NSPredicate*)predicate;

Returns the objects in an entity that match the constructed predicate, sorted
by the key value (which must be an attribute in the entity). Creates an
`NSSortDescriptor` object based on the `key` and `ascending` values. Use this
version and construct your `NSPredicate` value appropriately for predicate
parameters that contain user input.

    - (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                                 sortWith:(NSArray*)sortDescriptors
                      predicateWithFormat:(NSString*)predicateFormat, ...;

Returns the objects in an entity that match the predicate comparison rules,
sorted by the `NSArray` containing `NSSortDescriptor` objects. An `NSPredicate`
will be created using `[NSPredicate predicateWithFormat:arguments:]`. Fast and
easy, but unsafe for values that involve user input.

    - (NSArray*)fetchObjectsForEntityName:(NSString*)entityName
                                sortByKey:(NSString*)key
                                ascending:(BOOL)ascending
                      predicateWithFormat:(NSString*)predicateFormat, ...;

Returns the objects in an entity that match the constructed predicate, sorted
by the key value (which must be an attribute in the entity). Creates an
`NSSortDescriptor` object based on the `key` and `ascending` values. An
`NSPredicate` will be created using `[NSPredicate
predicateWithFormat:arguments:]`. Fast and easy, but unsafe for values that
involve user input.

## Background & Design Notes

As stated at the beginning, this is loosely based on [code][2] by Matt
Gallagher, where he writes:

> It's a lot easier to get your data out of Core Data than the documentation
> will tell you. This simple 1-line fetch will work just as well as Apple's
> suggested 10-line approach for most uses.

He points out that the [Core Data Programming Guide][3] gives a multi-line
approach to fetching data from a Core Data entity:

    NSManagedObjectContext *moc = [self managedObjectContext];
    NSEntityDescription *entityDescription = [NSEntityDescription entityForName:@"Employee"
                                                         inManagedObjectContext:moc];
    NSFetchRequest *request = [[[NSFetchRequest alloc] init] autorelease];
    [request setEntity:entityDescription];

    // Set example predicate and sort orderings...
    NSNumber *minimumSalary = ...;
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"(lastName LIKE[c] 'Worsley') AND (salary > %@)",
                                                              minimumSalary];
    [request setPredicate:predicate];

    NSSortDescriptor *sortDescriptor = [[NSSortDescriptor alloc] initWithKey:@"firstName" ascending:YES];
    [request setSortDescriptors:[NSArray arrayWithObject:sortDescriptor]];
    [sortDescriptor release];

    NSError *error = nil;
    NSArray *array = [moc executeFetchRequest:request error:&error];
    if (array == nil)
    {
        // Deal with error...
    }

Matt's sample code simplifies the above fetch to a single line:

    [[self managedObjectContext] fetchObjectsForEntityName:@"Employee"
                                             withPredicate:@"(lastName LIKE[c] 'Worsley') AND (salary > %@)",
                                             minimumSalary];

When I found this, it simplified my Core Data code significantly, but it turned
out to be insufficient for my purposes. Not only did I need filtering, I needed
sorting; I also had a couple of small cases where I just needed everything (the
equivalent of `SELECT * FROM Employee` in SQL).

Matt mentioned that his pattern of using `id` as the type of the
`withPredicate:` parameter was questionable design. Because it was `id`, he
could do some checking inside `fetchObjectsForEntityName:withPredicate:` to
determine whether the parameter was an `NSPredicate` or an `NSString` to be
converted into an `NSPredicate` with `predicateWithFormat:arguments:`. I've
written similar code in Ruby, but it didn't feel right for Objective-C. It also
made the string-formatted predicate too attractive for cases where your query
parameters might have been based on user input.

By time I was done adding the features I needed, I had changed this design to
be an explicit choice among multiple methods. Now, the resulting category
offers an explicit `NSPredicate` form (e.g.,
`fetchObjectsForEntityName:withPredicate`) and a `NSString`-formatted form
(e.g., `fetchObjectsForEntityName:predicateWithFormat`). It is easier to use
the `predicateWithFormat` methods, but it is safer to use the `withPredicate`
methods.

Finally, Matt's code returned `NSSet`, but this turned out to be a problem for
my data, so I am returning `NSArray` instead; it's trivial to add `[NSSet
setWithArray:results]` at the end to convert the returned data to a set if you
require an `NSSet` instead of an `NSArray`.

[1]: http://developer.apple.com/mac/library/DOCUMENTATION/Cocoa/Conceptual/CoreData/index.html "Core Data"
[2]: http://cocoawithlove.com/2008/03/core-data-one-line-fetch.html "Core Data: one line fetch, Matt Gallagher, Cocoa With Love, March 7, 2008"
[3]: http://developer.apple.com/documentation/Cocoa/Conceptual/CoreData/Articles/cdFetching.html "Core Data Programming Guide"
