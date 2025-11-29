#!/usr/bin/env bash

# --- Configuration ---
# Set the name of the directory to store backups (this will be excluded)
BACKUP_DIR="Backups"

# Create a unique filename with a timestamp
# Format: project-backup-YYYY-MM-DD_HH-MM-SS.tar.gz
FILENAME="$BACKUP_DIR/NoneScript-$(date +'%Y-%m-%d_%H-%M-%S').tar.gz"

# --- Main Script ---
echo "Starting backup..."

# Ensure the backup directory exists
# The '-p' flag means 'create if not exist, and don't error if it does'
mkdir -p "$BACKUP_DIR"

# The tar command:
# -c : create a new archive
# -z : compress with gzip
# -v : verbose (show files as they are added)
# -f : specify the output FILENAME
# '.' : target the current directory
tar -czvf "$FILENAME" \
    --exclude='../.git' \
    --exclude="../$BACKUP_DIR" \
    ..

# --- Completion ---
echo ""
echo "Backup complete!"
echo "Archive created at: $FILENAME"
