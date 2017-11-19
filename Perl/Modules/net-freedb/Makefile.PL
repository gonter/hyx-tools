use ExtUtils::MakeMaker;

WriteMakefile(
  'NAME'         => 'net::freedb',
  'VERSION_FROM' => 'lib/Net/freedb/file.pm',      # finds $VERSION
  'PREREQ_PM'    => {
     MD5 => 0,
  },    # e.g., Module::Name => 1.1
);

